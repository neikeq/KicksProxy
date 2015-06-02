#ifndef WORKERTASK_H
#define WORKERTASK_H

#include <QObject>
#include <QRunnable>

class WorkerTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit WorkerTask(QByteArray data, quint16 serverId);

    /**
     * @brief Must be called when ignoring a packet
     */
    void ignoreCurrent();

    inline int getWriterIndex() const { return writerIndex; }
    inline quint16 getServerId() const { return serverId; }

signals:
    void readComplete(int readerIndex);
    void write(const QByteArray &data, int writerIndex);
    void updateWriterIndex(int writerIndex);

public slots:

protected:
    void run();

private:
    /**
     * @brief Passes it to MessageHandler and writes it to the socket if not intercepted
     * @param The packet to read
     * @param The packet id
     */
    void readMessage(const QByteArray &data, quint32 messagdId);

    QByteArray data;
    quint16 serverId;
    int writerIndex;

};

#endif // WORKERTASK_H
