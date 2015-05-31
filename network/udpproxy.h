#ifndef UDPPROXY_H
#define UDPPROXY_H

#include <QObject>
#include <QUdpSocket>

class UdpProxy : public QObject
{
    Q_OBJECT
public:
    explicit UdpProxy(quint16 serverId, QObject *parent = 0);
    void writeDatagram(const QByteArray &datagram, const QString &address, quint16 port);

signals:

public slots:
    void readyRead();

private:
    QUdpSocket *socket;

};

#endif // UDPPROXY_H
