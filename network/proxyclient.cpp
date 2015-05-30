#include "network/proxyclient.h"

#include "settings.h"
#include "network/workertask.h"

ProxyClient::ProxyClient(QObject *parent) :
    QObject(parent)
{
    threadPool = new QThreadPool(this);
    threadPool->setMaxThreadCount(5);

    clientData = new QByteArray();
    serverData = new QByteArray();
}

void ProxyClient::initializeProxy(QTcpSocket *clientSocket, QTcpSocket *serverSocket)
{
    // Initialize client socket
    this->clientSocket = clientSocket;

    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(clientReadyRead()));

    // Initialize server socket

    this->serverSocket = serverSocket;

    connect(serverSocket, SIGNAL(disconnected()), this, SLOT(serverDisconnected()));
    connect(serverSocket, SIGNAL(readyRead()), this, SLOT(serverReadyRead()));
}

void ProxyClient::clientDisconnected()
{
    qDebug() << "Disconnected from client.";

    if (clientSocket != 0) {
        clientSocket->deleteLater();
        clientSocket = 0;
    }

    // Close the connection with the server
    threadPool->waitForDone();

    if (serverSocket != 0) {
        // Write any pending data to the server and delete the socket
        const QByteArray &data = clientData->right(clientData->size() - clientWriterIndex);

        serverSocket->write(data);
        serverSocket->flush();
        serverSocket->deleteLater();
        serverSocket = 0;
    }
}

void ProxyClient::clientReadyRead()
{
    if (clientSocket != 0) {
        this->clientWriterIndex = 0;

        clientData->append(clientSocket->readAll());

        WorkerTask *task = new WorkerTask(*clientData);
        task->setAutoDelete(true);

        connect(task, SIGNAL(readComplete(int)), this, SLOT(clientReadComplete(int)));
        connect(task, SIGNAL(write(QByteArray, int)), this, SLOT(clientWrite(QByteArray, int)));
        connect(task, SIGNAL(updateWriterIndex(int)), this, SLOT(updateClientWriterIndex(int)));

        threadPool->start(task);
    }
}

void ProxyClient::serverDisconnected()
{
    qDebug() << "Disconnected from server.";

    if (serverSocket != 0) {
        serverSocket->deleteLater();
        serverSocket = 0;
    }

    // Close the connection with the client
    threadPool->waitForDone();

    if (clientSocket != 0) {
        // Write any pending data to the client and delete the socket
        const QByteArray &data = serverData->right(serverData->size() - serverWriterIndex);

        clientSocket->write(data);
        clientSocket->flush();
        clientSocket->deleteLater();
        clientSocket = 0;
    }
}

void ProxyClient::serverReadyRead()
{
    if (serverSocket != 0) {
        this->serverWriterIndex = 0;

        serverData->append(serverSocket->readAll());

        WorkerTask *task = new WorkerTask(*serverData);
        task->setAutoDelete(true);

        connect(task, SIGNAL(readComplete(int)), this, SLOT(serverReadComplete(int)));
        connect(task, SIGNAL(write(QByteArray, int)), this, SLOT(serverWrite(QByteArray, int)));
        connect(task, SIGNAL(updateWriterIndex(int)), this, SLOT(updateServerWriterIndex(int)));

        threadPool->start(task);
    }
}

void ProxyClient::clientReadComplete(int readerIndex)
{
    // Clear readed data
    clientData->remove(0, readerIndex);

    if (serverSocket != 0 && serverSocket->isOpen())
        serverSocket->flush();
}

void ProxyClient::clientWrite(const QByteArray &data, int writerIndex)
{
    if (serverSocket != 0 && serverSocket->isWritable() && serverSocket->isOpen())
        serverSocket->write(data);

    if (writerIndex > 0) {
        this->clientWriterIndex = writerIndex;
    }
}

void ProxyClient::serverReadComplete(int readerIndex)
{
    // Clear readed data
    serverData->remove(0, readerIndex);

    if (clientSocket != 0 && clientSocket->isOpen())
        clientSocket->flush();
}

void ProxyClient::serverWrite(const QByteArray &data, int writerIndex)
{
    if (clientSocket != 0 && clientSocket->isWritable() && clientSocket->isOpen())
        clientSocket->write(data);

    if (writerIndex > 0) {
        this->serverWriterIndex = writerIndex;
    }
}
