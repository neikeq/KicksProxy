#include <QCoreApplication>
#include <QDebug>

#include "argumentsparser.h"
#include "network/proxyserver.h"
#include "network/servermanager.h"
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

    emit ServerManager::instance().addServer(99, Settings::instance().getServerAddress(),
                                        Settings::instance().getServerPort());

    return a.exec();
}
