#include "udpproxy.h"

#include "settings.h"

UdpProxy::UdpProxy(quint16 serverId, QObject *parent) :
    QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, Settings::UDP_PORT_FACTOR + serverId);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void UdpProxy::writeDatagram(const QByteArray &datagram, const QString &address, quint16 port)
{
    socket->writeDatagram(datagram, QHostAddress(address), port);
}

void UdpProxy::readyRead()
{
    QByteArray datagram;
    datagram.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
}
