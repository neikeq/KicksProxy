#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QObject>

enum class MessageType {
    ClientMessage,
    ServerMessage
};

class Constants
{
public:
    static const quint32 HEADER_SIZE;
    static const quint32 BODY_SIZE_INDEX;
    static const qint16 BIND_PORT;
    static const QString SERVER_ADDRESS;
    static const qint16 SERVER_PORT;
    static const qint16 GAME_PORT_FACTOR;
    static const quint8 XOR_KEY;
};

#endif // CONSTANTS_H
