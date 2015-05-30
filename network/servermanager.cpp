#include "network/servermanager.h"

#include "settings.h"

ServerManager::ServerManager(QObject *parent) :
    QObject(parent)
{
    connect(this, SIGNAL(addServer(quint16,QString,qint16)),
            this, SLOT(addProxyServer(quint16,QString,qint16)));
}

void ServerManager::addProxyServer(quint16 serverId, const QString &targetAddress, qint16 targetPort)
{
    ProxyServer *server = new ProxyServer(targetAddress, targetPort, this);
    server->startServer(Settings::instance().getProxyPortFactor() + serverId);

    servers.insert(serverId, server);
}
