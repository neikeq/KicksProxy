#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QMap>
#include <QObject>

#include "network/proxyserver.h"

class ServerManager : public QObject
{
    Q_OBJECT
public:
    static ServerManager& instance()
    {
        static ServerManager instance;
        return instance;
    }

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

    QMap<quint16, ProxyServer*> servers;

};

#endif // SERVERMANAGER_H
