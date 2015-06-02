#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>

#include "network/proxyserver.h"
#include "network/udpserver.h"

class ServerManager : public QObject
{
    Q_OBJECT
public:
    static ServerManager& instance()
    {
        static ServerManager instance;
        return instance;
    }

    inline UdpServer* getUdpServer(quint16 serverId) const { return udpServers[serverId]; }

signals:
    void addServer(quint16 serverId, const QString &targetAddress, quint16 targetPort);

public slots:
    void addProxyServer(quint16 serverId, const QString &targetAddress, quint16 targetPort);
    void removeServer();
private:
    explicit ServerManager(QObject *parent = 0);

    // To avoid getting copies of this singleton
    ServerManager(ServerManager const&) = delete;
    void operator=(ServerManager const&) = delete;

    QHash<quint16, ProxyServer*> servers;
    QHash<quint16, UdpServer*> udpServers;

};

#endif // SERVERMANAGER_H
