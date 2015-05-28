#include "proxyserver.h"

#include "constants.h"
#include "proxyclient.h"

ProxyServer::ProxyServer(QObject *parent) :
    QTcpServer(parent)
{
}

void ProxyServer::startServer()
{
    if (listen(QHostAddress::Any, Constants::BIND_PORT)) {
        qDebug() << "Listening on port " << Constants::BIND_PORT;
    } else {
        qDebug() << "Error when trying to listen on port " << Constants::BIND_PORT;
    }
}

void ProxyServer::incomingConnection(qintptr handle)
{
    // Initialize proxy between client and server
    ProxyClient *client = new ProxyClient(this);
    client->initializeProxy(handle);
}
