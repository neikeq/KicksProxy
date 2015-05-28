#ifndef PROXYCLIENT_H
#define PROXYCLIENT_H

#include <QByteArray>
#include <QObject>
#include <QTcpSocket>
#include <QThreadPool>

class ProxyClient : public QObject
{
    Q_OBJECT
public:
    explicit ProxyClient(QObject *parent = 0);

    void clientConnected(int descriptor);

signals:

public slots:
    // socket slots
    void clientConnected();
    void clientDisconnected();
    void clientReadyRead();
    void serverConnected();
    void serverDisconnected();
    void serverReadyRead();

    // worker thread slots
    void clientReadComplete(int readerIndex);
    void clientWrite(const QByteArray &data, int writerIndex);
    void serverReadComplete(int readerIndex);
    void serverWrite(const QByteArray &data, int writerIndex);

    inline void updateClientWriterIndex(int writerIndex)
    {
        clientWriterIndex = writerIndex;
    }

    inline void updateServerWriterIndex(int writerIndex)
    {
        serverWriterIndex = writerIndex;
    }

private:
    void connectToServer();

    QThreadPool *threadPool;

    QTcpSocket *clientSocket;
    QTcpSocket *serverSocket;

    QByteArray *clientData;
    QByteArray *serverData;

    int clientWriterIndex;
    int serverWriterIndex;
};

#endif // PROXYCLIENT_H
