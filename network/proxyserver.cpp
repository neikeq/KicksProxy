#include "network/proxyserver.h"

#include "settings.h"
#include "network/proxyclient.h"

ProxyServer::ProxyServer(QObject *parent) :
    QTcpServer(parent)
{
}

void ProxyServer::startServer()
{
    qint16 proxyPort = Settings::getInstance().getProxyPort();

    if (listen(QHostAddress::Any, proxyPort)) {
        qDebug() << "Listening on port " << proxyPort;
    } else {
        qDebug() << "Error when trying to listen on port " << proxyPort;
    }
}

void ProxyServer::incomingConnection(qintptr handle)
{
    // Initialize proxy between client and server
    ProxyClient *client = new ProxyClient(this);
    client->initializeProxy(handle);
}
