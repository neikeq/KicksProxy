#include "singleinstance.h"

#include <QDebug>

#include "argumentsparser.h"

SingleInstance::SingleInstance(QObject *parent) :
    QObject(parent)
{
    connect(&server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void SingleInstance::listen(const QString &name)
{
    server.removeServer(name);

    if (server.listen(name))
        qDebug() << "Listening on: " << name;
    else
        qDebug() << server.errorString();
}

bool SingleInstance::instanceExists(const QString &name, const QStringList &arguments)
{
    qDebug() << "Checking if a previous instance exists...";

    QLocalSocket socket;
    socket.connectToServer(name, QLocalSocket::ReadWrite);

    bool instanceExists = socket.waitForConnected();

    if (instanceExists) {
        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out << arguments;

        socket.write(data);
        socket.flush();
    } else if (socket.error() != QLocalSocket::ConnectionRefusedError) {
        qDebug() << socket.errorString();
        qDebug() << socket.error();
    }

    return instanceExists;
}

void SingleInstance::newConnection()
{
    socket = server.nextPendingConnection();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void SingleInstance::readyRead()
{
    QByteArray data = socket->readAll();
    QDataStream in(&data, QIODevice::ReadOnly);

    QStringList arguments;
    in >> arguments;

    qDebug() << "Received arguments: " << arguments;

    ArgumentsParser::instance().parseArguments(arguments);

    socket->deleteLater();
}
