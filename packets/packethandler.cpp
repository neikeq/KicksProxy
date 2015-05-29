#include "packets/packethandler.h"

#include <QDebug>

#include "settings.h"
#include "packets/packetid.h"

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
        clientCertifyLogin(workerTask, bytes);
    });

    // Server Events

    events.insert(PacketId::CERTIFY_LOGIN,
                        [=] (WorkerTask *workerTask, const QByteArray &bytes) {
        serverCertifyLogin(workerTask, bytes);
    });
}

void PacketHandler::clientCertifyLogin(WorkerTask *workerTask, const QByteArray &bytes)
{
    qDebug() << "Received client's CertifyLogin with size: " << bytes.size();

    emit workerTask->write(bytes, workerTask->getWriterIndex());
}

void PacketHandler::serverCertifyLogin(WorkerTask *workerTask, const QByteArray &bytes)
{
    qDebug() << "Received server's CertifyLogin with size: " << bytes.size();

    // Ignore the packet so the client will not receive it
    workerTask->ignoreCurrent();
}
