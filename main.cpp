#include <QCoreApplication>
#include <QDebug>

#include "argumentsparser.h"
#include "network/proxyserver.h"
#include "settings.h"
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

    ArgumentsParser::instance().parseArguments(QCoreApplication::arguments());

    ProxyServer server;
    server.startServer(Settings::instance().getProxyPort());

    return a.exec();
}
