#include "network/servermanager.h"

#include <QDebug>

#include "settings.h"

ServerManager::ServerManager(QObject *parent) :
    QObject(parent)
{
    connect(this, SIGNAL(addServer(quint16,QString,quint16)),
            this, SLOT(addProxyServer(quint16,QString,quint16)));
}

void ServerManager::addProxyServer(quint16 serverId, const QString &targetAddress, quint16 targetPort)
{
    if (!servers.contains(serverId)) {
        ProxyServer *server = new ProxyServer(targetAddress, targetPort, serverId, this);
        bool started = server->startServer(Settings::instance().getProxyPortFactor() + serverId);

        if (started) {
            connect(server, SIGNAL(disconnected()), this, SLOT(removeServer()));
            servers.insert(serverId, server);
        } else {
            server->deleteLater();
        }
    }
}

void ServerManager::removeServer()
{
    if (sender() != 0) {
        ProxyServer *server = static_cast<ProxyServer*>(sender());
        quint16 serverId = server->getServerId();

        // If not the main server, delete it
        if (serverId != 99) {
            qDebug() << "Proxy server removed: " << server->getServerId();

            servers.remove(serverId);
            server->deleteLater();
        }
    }
}
