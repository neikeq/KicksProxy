#include "network/proxyserver.h"

#include "settings.h"
#include "network/proxyclient.h"

ProxyServer::ProxyServer(const QString &targetAddress, qint16 targetPort, QObject *parent) :
    QTcpServer(parent)
{
    this->targetAddress = targetAddress;
    this->targetPort = targetPort;
}

void ProxyServer::startServer(qint16 port)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(newIncomingConnection()));

    if (listen(QHostAddress::Any, port))
        qDebug() << "Listening on port " << port;
    else
        qDebug() << "Error when trying to listen on port " << port;
}

void ProxyServer::newIncomingConnection()
{
    // Initialize proxy between client and server
    ProxyClient *client = new ProxyClient(this);

    QTcpSocket *clientSocket = this->nextPendingConnection();
    QTcpSocket *serverSocket = new QTcpSocket(this);

    connect(serverSocket, SIGNAL(connected()), client, SLOT(serverConnected()));

    serverSocket->connectToHost(targetAddress, targetPort);

    if (serverSocket->waitForConnected()) {
        qDebug() << "Connected to server.";
        client->initializeProxy(clientSocket, serverSocket);
    } else {
        // The connection with server failed, close the client socket
        qDebug() << "Cannot connect to server.";
        clientSocket->deleteLater();
    }
}
