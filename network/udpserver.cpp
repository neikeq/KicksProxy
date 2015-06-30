#include "network/udpserver.h"

#include "packets/packetid.h"
#include "settings.h"

UdpServer::UdpServer(quint16 serverId, const QString &serverAddress, QObject *parent) :
    QObject(parent)
{
    this->serverAddress = QHostAddress(serverAddress);
    serverPort = Settings::instance().getServerUdpPortFactor() + serverId;
    bindPort = Settings::instance().getProxyUdpPortFactor() + serverId;

    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->bind(QHostAddress::Any, bindPort);

    connect(this, SIGNAL(clearPlayerMap(quint32)), this, SLOT(onClearPlayerMap(quint32)));
    connect(this, SIGNAL(removePlayer(quint32,quint32)),
            this, SLOT(onRemovePlayer(quint32,quint32)));
    connect(this, SIGNAL(setPlayerInfo(quint32,quint32,QString,quint16)),
            this, SLOT(onSetPlayerInfo(quint32,quint32,QString,quint16)));
    connect(this, SIGNAL(setPlayerPort(quint32,quint32,quint16)),
            this, SLOT(onSetPlayerPort(quint32,quint32,quint16)));
}

void UdpServer::writeDatagram(const QByteArray &datagram, const QHostAddress &address, quint16 port)
{
    socket->writeDatagram(datagram, address, port);
}

void UdpServer::readyRead()
{
    QByteArray datagram;
    datagram.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

    quint32 senderId = 0;
    quint32 targetId = 0;
    quint16 bodySize = 0;
    quint32 packetId = 0;

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setByteOrder(QDataStream::LittleEndian);
    in.skipRawData(2);
    in >> senderId;
    in >> targetId;
    in >> bodySize;

    if (bodySize < 4)
        return;

    in >> packetId;

    bool isServerDatagram = senderPort == serverPort;

    quint32 playerId = isServerDatagram ? 0 : (senderPort == bindPort ? targetId : senderId);

    PLAYER_INFO_MAP &players = playerMaps[playerId];

    if ((packetId == PacketId::UDP_PING || packetId == PacketId::UDP_AUTHENTICATE)
            && !isServerDatagram) {
        writeDatagram(datagram, serverAddress, serverPort);
    } else {
        PlayerInfo &playerInfo = players[targetId];
        writeDatagram(datagram, playerInfo.address, playerInfo.port);
    }

    bool updatedPort = false;

    if (!isServerDatagram && playerId == senderId) {
        if (!players.contains(playerId)) {
            PlayerInfo senderInfo;

            senderInfo.address = sender;
            senderInfo.port = senderPort;

            players.insert(playerId, senderInfo);

            updatedPort = true;
        } else {
            PlayerInfo &playerInfo = players[playerId];

            if (playerInfo.port != senderPort) {
                PlayerInfo &senderInfo = players[playerId];

                senderInfo.address = sender;
                senderInfo.port = senderPort;

                updatedPort = true;
            }
        }
    }

    if (updatedPort)
        writeDatagram(updatePortPacket(playerId, senderPort), serverAddress, serverPort);
}

QByteArray UdpServer::updatePortPacket(quint32 playerId, quint16 port)
{
    QByteArray datagram;

    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);

    out << static_cast<quint16>(0);
    out << playerId;
    out << static_cast<quint32>(0);
    out << static_cast<quint16>(6);
    out << PacketId::PROXY_UPDATE_PORT;
    out << port;

    return datagram;
}

void UdpServer::onSetPlayerInfo(quint32 mapId, quint32 playerId, QString address, quint16 port)
{
    if (!playerMaps.contains(mapId))
        playerMaps.insert(mapId, PLAYER_INFO_MAP());

    PLAYER_INFO_MAP &players = playerMaps[mapId];

    if (players.contains(playerId)) {
        PlayerInfo &playerInfo = players[playerId];

        playerInfo.address = address;
        playerInfo.port = port;
    } else {
        PlayerInfo playerInfo;

        playerInfo.address = address;
        playerInfo.port = port;

        players.insert(playerId, playerInfo);
    }
}

void UdpServer::onSetPlayerPort(quint32 mapId, quint32 playerId, quint16 port)
{
    if (!playerMaps.contains(mapId))
        return;

    PLAYER_INFO_MAP &players = playerMaps[mapId];

    if (players.contains(playerId)) {
        PlayerInfo &playerInfo = players[playerId];
        playerInfo.port = port;
    }
}

void UdpServer::onClearPlayerMap(quint32 mapId)
{
    PLAYER_INFO_MAP &players = playerMaps[mapId];
    PlayerInfo playerInfo = players[mapId];
    players.clear();
    players.insert(mapId, playerInfo);

}

void UdpServer::onRemovePlayer(quint32 mapId, quint32 playerId)
{
    playerMaps[mapId].remove(playerId);
}
