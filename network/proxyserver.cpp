#include "network/proxyserver.h"

#include "settings.h"

ProxyServer::ProxyServer(const QString &targetAddress, quint16 targetPort,
                         quint16 serverId, QObject *parent) : QTcpServer(parent)
{
    this->serverId = serverId;
    this->targetAddress = targetAddress;
    this->targetPort = targetPort;
}

bool ProxyServer::startServer(quint16 port)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    bool listening = listen(QHostAddress::Any, port);

    if (listening)
        qDebug() << "Listening on port " << port;
    else
        qDebug() << this->errorString();

    return listening;
}

void ProxyServer::onNewConnection()
{
    // Initialize proxy between client and server
    ProxyClient *client = new ProxyClient(this);

    connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    clients.append(client);

    QTcpSocket *clientSocket = this->nextPendingConnection();
    QTcpSocket *serverSocket = new QTcpSocket(this);

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

void ProxyServer::clientDisconnected()
{
    if (sender() != 0) {
        ProxyClient *client = static_cast<ProxyClient*>(sender());

        int index = clients.indexOf(client);

        if (index != -1) {
            clients.remove(index);
        }

        delete client;

        if (clients.size() == 0) {
            emit disconnected();
        }
    }
}
