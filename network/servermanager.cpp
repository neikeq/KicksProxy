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

            if (serverId != Settings::MAIN_SERVER_ID && !udpServers.contains(serverId)) {
                UdpServer *udpServer = new UdpServer(serverId, targetAddress, this);
                udpServers.insert(serverId, udpServer);
            }
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
        if (serverId != Settings::MAIN_SERVER_ID) {
            qDebug() << "Proxy server removed: " << server->getServerId();

            UdpServer* udpServer = udpServers[serverId];

            servers.remove(serverId);
            udpServers.remove(serverId);

            server->deleteLater();
            udpServer->deleteLater();
        }
    }
}
