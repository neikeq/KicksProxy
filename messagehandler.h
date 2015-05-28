#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <functional>
#include <QMap>
#include <QObject>

#include "workertask.h"

class MessageHandler
{
public:
    static MessageHandler& getInstance()
    {
        static MessageHandler instance;
        return instance;
    }

    bool handle(int messageId, const QByteArray &bytes, WorkerTask *workerTask);

private:
    MessageHandler();

    // To avoid getting copies of this singleton
    MessageHandler(MessageHandler const&) = delete;
    void operator=(MessageHandler const&) = delete;

    QMap<quint32, std::function<void(WorkerTask *workerTask, const QByteArray &bytes)>> events;

    // Message event methods
    void clientCertifyLogin(WorkerTask *workerTask, const QByteArray &bytes);
    void serverCertifyLogin(WorkerTask *workerTask, const QByteArray &bytes);
};

#endif // MESSAGEHANDLER_H
