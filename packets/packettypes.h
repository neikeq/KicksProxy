#ifndef PACKETS_H
#define PACKETS_H

#include <QObject>

#pragma pack(push, 1)

class PHeader
{
public:
    quint16 flag;
    quint32 playerId;
    quint32 targetId;
    quint16 bodySize;
};

#pragma pack(pop)

#endif // PACKETS_H
