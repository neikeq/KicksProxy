#ifndef PACKETS_H
#define PACKETS_H

#include <QObject>

#pragma pack(push, 1)

class PacketHeader
{
public:
    quint16 flag;
    quint32 playerId;
    quint32 targetId;
    quint16 bodySize;
};

class SCServerInfo
{
public:
    quint32 packetId;
    quint16 response;
    quint16 serverId;
    quint16 serverType;
    quint16 minLevel;
    quint16 maxLevel;
    char serverIp[16];
    quint16 serverPort;
};

#pragma pack(pop)

#endif // PACKETS_H
