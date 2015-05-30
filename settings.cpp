#include "settings.h"

#include <QSettings>

const quint32 Settings::HEADER_SIZE = 12;
const quint32 Settings::BODY_SIZE_INDEX = 10;
const quint8 Settings::XOR_KEY = 229;

Settings::Settings()
{
    QSettings settings("proxy.ini", QSettings::IniFormat);

    settings.beginGroup("Server");
    serverAddress = settings.value("Address").toString();
    serverPort = settings.value("Port").toInt();
    settings.endGroup();

    settings.beginGroup("Proxy");
    proxyPortFactor = settings.value("PortFactor").toInt();
    settings.endGroup();
}
