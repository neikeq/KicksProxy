#include "singleinstance.h"

SingleInstance::SingleInstance(QObject *parent) :
    QObject(parent)
{
    connect(&server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void SingleInstance::listen(QString name)
{
    server.removeServer(name);
    server.listen(name);

    qDebug() << "Listening on: " << name;
    qDebug() << server.errorString();
}

bool SingleInstance::instanceExists(QString name)
{
    qDebug() << "Checking if a previous instance exists...";

    QLocalSocket socket;
    socket.connectToServer(name, QLocalSocket::ReadWrite);

    bool instanceExists = socket.waitForConnected();

    qDebug() << socket.errorString();

    return instanceExists;
}

void SingleInstance::newConnection()
{
    socket = server.nextPendingConnection();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void SingleInstance::readyRead()
{
    socket->deleteLater();
}
