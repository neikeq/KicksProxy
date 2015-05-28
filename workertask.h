#ifndef WORKERTASK_H
#define WORKERTASK_H

#include <QObject>
#include <QRunnable>

class WorkerTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit WorkerTask(QByteArray data);

    void ignoreCurrent();

    inline int getWriterIndex() const { return writerIndex; }

signals:
    void readComplete(int readerIndex);
    void write(const QByteArray &data, int writerIndex);
    void updateWriterIndex(int writerIndex);

public slots:

protected:
    void run();

private:
    void readMessage(const QByteArray &data, quint32 messagdId);

    int writerIndex;
    QByteArray data;

};

#endif // WORKERTASK_H
