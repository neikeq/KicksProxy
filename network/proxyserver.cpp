#include "network/proxyserver.h"

#include "settings.h"
#include "network/proxyclient.h"

ProxyServer::ProxyServer(QObject *parent) :
    QTcpServer(parent)
{
}

void ProxyServer::startServer(qint16 port)
{
    if (listen(QHostAddress::Any, port))
        qDebug() << "Listening on port " << port;
    else
        qDebug() << "Error when trying to listen on port " << port;
}

void ProxyServer::incomingConnection(qintptr handle)
{
    // Initialize proxy between client and server
    ProxyClient *client = new ProxyClient(this);
    client->initializeProxy(handle);
}
