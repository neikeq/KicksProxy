#include <QCoreApplication>
#include <QDebug>

#include "network/proxyserver.h"
#include "singleinstance.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("KicksProxy");

    QString name = "com.neikeq.kicksproxy";

    SingleInstance singleInstance;

    if (singleInstance.instanceExists(name, QCoreApplication::arguments())) {
        qDebug() << "An instance is already running!";
        return 0;
    }

    singleInstance.listen(name);

    ProxyServer server;
    server.startServer();

    return a.exec();
}
