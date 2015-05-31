#include "packets/packethandler.h"

#include <QDebug>

#include "settings.h"
#include "settings.h"
#include "packets/packetid.h"
#include "packets/packettypes.h"
#include "network/servermanager.h"

bool PacketHandler::handle(int messageId, const QByteArray &bytes, WorkerTask *workerTask)
{
    auto func = events.value(messageId, NULL);

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
}

void PacketHandler::serverServerInfo(WorkerTask *workerTask, const QByteArray &bytes)
{
    PacketHeader *header = reinterpret_cast<PacketHeader*>
            (bytes.left(Settings::HEADER_SIZE).data());
    SCServerInfo *body = reinterpret_cast<SCServerInfo*>
            (bytes.mid(Settings::HEADER_SIZE, header->bodySize).data());

    QString serverAddress = QString(body->serverIp);
    quint16 serverPort = body->serverPort;

    static QByteArray localhost = QString("127.0.0.1\0").toLocal8Bit();
    memcpy(body->serverIp, localhost.constData(), localhost.size() + 1);

    body->serverPort = Settings::instance().getProxyPortFactor() + body->serverId;

    QByteArray modified(reinterpret_cast<char*>(header), sizeof(*header));
    modified.append(reinterpret_cast<char*>(body), sizeof(*body));

    emit ServerManager::instance().addServer(body->serverId, serverAddress, serverPort);

    emit workerTask->write(modified, workerTask->getWriterIndex());
}
