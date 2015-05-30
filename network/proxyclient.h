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

    /**
     * @brief Initializes the proxy between client and server
     * @param Socket descriptor for the client connection
     */
    void initializeProxy(QTcpSocket *clientSocket, QTcpSocket *serverSocket);

signals:

public slots:
    // socket slots
    void clientDisconnected();
    void clientReadyRead();
    void serverDisconnected();
    void serverReadyRead();

    // worker thread slots
    /**
     * @brief Called when the read was completed by the worker thread
     * @param Current reader position in the data array
     */
    void clientReadComplete(int readerIndex);
    void serverReadComplete(int readerIndex);

    /**
     * @brief Writes the specified byte array to the socket
     * @param The byte array to write
     * @param Current writer position in the data array
     */
    void clientWrite(const QByteArray &data, int writerIndex);
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
    QThreadPool *threadPool;

    QTcpSocket *clientSocket;
    QTcpSocket *serverSocket;

    QByteArray *clientData;
    QByteArray *serverData;

    int clientWriterIndex;
    int serverWriterIndex;
};

#endif // PROXYCLIENT_H
