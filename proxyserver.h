#ifndef PROXYSERVER_H
#define PROXYSERVER_H

#include <QAbstractSocket>
#include <QTcpServer>
#include <QTcpSocket>

class ProxyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ProxyServer(QObject *parent = 0);
    void startServer();

protected:
    void incomingConnection(qintptr handle);

signals:

public slots:

};

#endif // PROXYSERVER_H
