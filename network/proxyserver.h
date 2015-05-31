#ifndef PROXYSERVER_H
#define PROXYSERVER_H

#include <QAbstractSocket>
#include <QTcpServer>
#include <QTcpSocket>

#include "network/proxyclient.h"

class ProxyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ProxyServer(const QString &targetAddress, quint16 targetPort,
                         quint16 serverId, QObject *parent = 0);

    /**
     * @brief Starts listening for new connections
     */
    bool startServer(quint16 port);

    /**
     * @brief Returns the amount of proxy clients alive
     * @return the amount of clients
     */
    int connectedClients();

    inline quint16 getServerId() const { return serverId; }
signals:
    void disconnected();

public slots:
    void onNewConnection();
    void clientDisconnected();
private:
    QVector<ProxyClient*> clients;

    QString targetAddress;
    quint16 targetPort;
    quint16 serverId;

};

#endif // PROXYSERVER_H
