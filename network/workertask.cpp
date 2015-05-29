#include "network/workertask.h"

#include <QDebug>
#include <QDataStream>
#include <QIODevice>

#include "settings.h"
#include "packets/packethandler.h"

WorkerTask::WorkerTask(QByteArray data)
{
    this->data = data;
    this->writerIndex = 0;
}

void WorkerTask::ignoreCurrent()
{
    emit updateWriterIndex(writerIndex);
}

void WorkerTask::run()
{
    int readerIndex = 0;
    int length = data.size();

    QDataStream stream(&data, QIODevice::ReadOnly);
    stream.setByteOrder(QDataStream::LittleEndian);

    quint16 bodySize = 0;
    quint16 bytesReaded = 0;

    do {
        bytesReaded = 0;

        quint32 readableBytes = length - readerIndex;

        if (readableBytes >= Settings::HEADER_SIZE) {
            int skip = Settings::BODY_SIZE_INDEX;

            if (readerIndex > 0)
                skip += bodySize - 4;

            stream.skipRawData(skip);
            stream >> bodySize;

            quint16 totalSize = bodySize + Settings::HEADER_SIZE;

            if (readableBytes >= totalSize) {
                quint32 messageId;
                stream >> messageId;

                writerIndex += totalSize;

                readMessage(data.mid(readerIndex, totalSize), messageId);

                readerIndex = writerIndex;
                bytesReaded = totalSize;
            }
        }
    } while (bytesReaded > 0);

    emit readComplete(readerIndex);
}

void WorkerTask::readMessage(const QByteArray &data, quint32 messageId)
{
    //const PHeader *header = reinterpret_cast<const PHeader*>(data.left(12).constData());

    bool intercepted = PacketHandler::instance().handle(messageId, data, this);

    if (!intercepted)
        emit write(data, writerIndex);
}
