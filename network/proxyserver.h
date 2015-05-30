#ifndef PROXYSERVER_H
#define PROXYSERVER_H

#include <QAbstractSocket>
#include <QTcpServer>
#include <QTcpSocket>

class ProxyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ProxyServer(const QString &targetAddress, qint16 targetPort, QObject *parent = 0);

    /**
     * @brief Starts listening for new connections
     */
    void startServer(qint16 port);

signals:

public slots:
    void newIncomingConnection();

private:
    QString targetAddress;
    qint16 targetPort;

};

#endif // PROXYSERVER_H
