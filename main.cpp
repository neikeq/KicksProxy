#include <QCoreApplication>
#include <QDebug>
#include <QProcess>

#include "argumentsparser.h"
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

    Settings &settings = Settings::instance();
    QString sUdpPort = QString::number(settings.getProxyUdpPortFactor());

    // upnpc -a ip port external_port tcp | udp

    QStringList command;
    command << settings.getUPnPcPath();
    command << "-a";
    command << settings.getLocalAddress().toString();
    command << sUdpPort;
    command << sUdpPort;
    command << "udp";

    QProcess::execute(command.join(QChar::Space));

    emit ServerManager::instance().addServer(Settings::MAIN_SERVER_ID,
                                             settings.getServerAddress(),
                                             settings.getServerPort());
    return a.exec();
}
