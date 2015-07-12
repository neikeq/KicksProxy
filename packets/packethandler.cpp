#include "packets/packethandler.h"

#include "settings.h"
#include "packets/packetid.h"
#include "network/servermanager.h"

bool PacketHandler::handle(int messageId, const QByteArray &bytes, WorkerTask *workerTask)
{
    auto func = events[messageId];

    if (func != NULL) {
        func(workerTask, bytes);
    }

    return func != NULL;
}

PacketHandler::PacketHandler()
{
    // Client Events

    static quint32 intKey = (Settings::XOR_KEY << 24) | (Settings::XOR_KEY << 16) |
                   (Settings::XOR_KEY << 8) | Settings::XOR_KEY;

    events.insert(PacketId::CERTIFY_LOGIN ^ intKey,
                  [=] (WorkerTask *workerTask, const QByteArray &bytes) {
        //workerTask->ignoreCurrent(); // Ignore the packet so the client will not receive it
        emit workerTask->write(bytes, workerTask->getWriterIndex());
    });

    // Server Events

    events.insert(PacketId::SERVER_INFO,
                  [=] (WorkerTask *workerTask, const QByteArray &bytes) {
        serverServerInfo(workerTask, bytes);
    });

    events.insert(PacketId::PLAYER_INFO,
                  [=] (WorkerTask *workerTask, const QByteArray &bytes) {
        serverPlayerInfo(workerTask, bytes);
    });

    events.insert(PacketId::ROOM_PLAYER_INFO,
                  [=] (WorkerTask *workerTask, const QByteArray &bytes) {
        serverRoomPlayerInfo(workerTask, bytes);
    });

    events.insert(PacketId::LEAVE_ROOM,
                  [=] (WorkerTask *workerTask, const QByteArray &bytes) {
        serverLeaveRoom(workerTask, bytes);
    });
}

void PacketHandler::serverServerInfo(WorkerTask *workerTask, const QByteArray &bytes)
{
    QString serverAddress(bytes.mid(26, 42));
    quint16 serverPort = 0;
    quint16 serverId = 0;

    QDataStream in(bytes);
    in.setByteOrder(QDataStream::LittleEndian);
    in.skipRawData(18);
    in >> serverId;
    in.skipRawData(22);
    in >> serverPort;

    QByteArray modified;
    QDataStream out(&modified, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);

    modified.append(bytes.left(26));
    modified.append(Settings::LOCALHOST.toLocal8Bit().constData());
    modified.append(QByteArray(16 - Settings::LOCALHOST.size(), '\0'));

    out.skipRawData(modified.size());
    out << static_cast<quint16>(Settings::instance().getProxyPortFactor() + serverId);

    emit ServerManager::instance().addServer(serverId, serverAddress, serverPort);

    emit workerTask->write(modified, workerTask->getWriterIndex());
}

void PacketHandler::serverPlayerInfo(WorkerTask *workerTask, const QByteArray &bytes)
{
    quint32 playerId = 0;

    QDataStream in(bytes);
    in.setByteOrder(QDataStream::LittleEndian);
    in.skipRawData(18);
    in >> playerId;

    emit workerTask->setPlayerId(playerId);

    emit workerTask->write(bytes, workerTask->getWriterIndex());
}

void PacketHandler::serverRoomPlayerInfo(WorkerTask *workerTask, const QByteArray &bytes)
{
    QString playerAddress(bytes.mid(63, 16));
    quint32 targetId = 0;
    quint32 playerId = 0;
    quint16 playerPort;

    QDataStream in(bytes);
    in.setByteOrder(QDataStream::LittleEndian);
    in.skipRawData(6);
    in >> targetId;
    in.skipRawData(8);
    in >> playerId;
    in.skipRawData(57);
    in >> playerPort;

    if (targetId != playerId) {
        quint16 serverId = workerTask->getServerId();
        quint16 proxyPort = Settings::instance().getProxyUdpPortFactor();
        UdpServer *udpServer = ServerManager::instance().getUdpServer(serverId);
        emit udpServer->setPlayerInfo(targetId, playerId, playerAddress, proxyPort);
    } else {
        UdpServer *udpOutterServer = ServerManager::instance().getUdpServer(0);
        emit udpOutterServer->setPlayerInfo(targetId, playerId, playerAddress, playerPort);
    }

    emit workerTask->write(bytes, workerTask->getWriterIndex());
}

void PacketHandler::serverLeaveRoom(WorkerTask *workerTask, const QByteArray &bytes)
{
    quint32 targetId = 0;
    quint32 playerId = 0;

    QDataStream in(bytes);
    in.setByteOrder(QDataStream::LittleEndian);
    in.skipRawData(6);
    in >> targetId;
    in.skipRawData(8);
    in >> playerId;

    quint16 serverId = workerTask->getServerId();

    UdpServer *udpServer = ServerManager::instance().getUdpServer(serverId);

    if (playerId == targetId) {
        emit udpServer->clearPlayerMap(targetId);

        UdpServer *udpOutterServer = ServerManager::instance().getUdpServer(0);
        emit udpOutterServer->clearPlayerMap(targetId);
    } else {
        emit udpServer->removePlayer(targetId, playerId);
    }

    emit workerTask->write(bytes, workerTask->getWriterIndex());
}
