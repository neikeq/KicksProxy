#include "network/udpserver.h"

#include "packets/packetid.h"
#include "settings.h"

UdpServer::UdpServer(quint16 serverId, const QString &serverAddress, QObject *parent) :
    QObject(parent)
{
    this->serverAddress = QHostAddress(serverAddress);
    this->serverPort = Settings::instance().getServerUdpPortFactor() + serverId;

    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->bind(QHostAddress::Any, Settings::UDP_PORT_FACTOR + serverId);

    connect(this, SIGNAL(clearPlayerMap(quint32)), this, SLOT(onClearPlayerMap(quint32)));
    connect(this, SIGNAL(setPlayerInfo(quint32,quint32,QString,quint16)),
            this, SLOT(onSetPlayerInfo(quint32,quint32,QString,quint16)));
    connect(this, SIGNAL(removePlayer(quint32,quint32)),
            this, SLOT(onRemovePlayer(quint32,quint32)));
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

    if (bodySize >= 4) {
        in >> packetId;
    }

    bool isServerDatagram = senderPort == serverPort;

    quint32 playerId = isServerDatagram ? 0 : senderId;

    PLAYER_INFO_MAP players = playerMaps[playerId];

    if (packetId == PacketId::UDP_PING && !isServerDatagram) {
        writeDatagram(datagram, serverAddress, serverPort);

        if (players.contains(playerId)) {
            PlayerInfo senderInfo = players[playerId];

            senderInfo.address = sender;
            senderInfo.port = senderPort;
        } else {
            PlayerInfo senderInfo;

            senderInfo.address = sender;
            senderInfo.port = senderPort;

            players.insert(playerId, senderInfo);
        }
    } else {
        PlayerInfo playerInfo = players[targetId];
        writeDatagram(datagram, playerInfo.address, playerInfo.port);
    }
}

void UdpServer::onSetPlayerInfo(quint32 mapId, quint32 playerId,
                              QString address, quint16 port)
{
    if (!playerMaps.contains(mapId)) {
        playerMaps.insert(mapId, PLAYER_INFO_MAP());
    }

    PLAYER_INFO_MAP& players = playerMaps[mapId];

    if (players.contains(playerId)) {
        PlayerInfo playerInfo = players[playerId];

        playerInfo.address = address;
        playerInfo.port = port;
    } else {
        PlayerInfo playerInfo;

        playerInfo.address = address;
        playerInfo.port = port;

        players.insert(playerId, playerInfo);
    }
}

// TODO call when client is disconnecting
void UdpServer::onClearPlayerMap(quint32 mapId)
{
    playerMaps[mapId].clear();
}

void UdpServer::onRemovePlayer(quint32 mapId, quint32 playerId)
{
    playerMaps[mapId].remove(playerId);
}
