#ifndef SETTINGS_H
#define SETTINGS_H

#include <QHostAddress>
#include <QObject>

class Settings
{
public:
    static const quint32 BODY_SIZE_INDEX;
    static const quint32 HEADER_SIZE;
    static const QString LOCALHOST;
    static const quint16 MAIN_SERVER_ID;
    static const quint8 XOR_KEY;

    inline const QString& getUPnPcPath() const { return uPnPcPath; }
    inline const QString& getServerAddress() const { return serverAddress; }
    inline int getServerPort() const { return serverPort; }
    inline int getProxyPortFactor() const { return proxyPortFactor; }
    inline int getProxyUdpPortFactor() const { return proxyUdpPortFactor; }
    inline int getServerUdpPortFactor() const { return serverUdpPortFactor; }
    QHostAddress getLocalAddress();

    static Settings& instance()
    {
        static Settings instance;
        return instance;
    }

private:
    Settings();

    // To avoid getting copies of this singleton
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;

    QString uPnPcPath;
    QString serverAddress;
    quint16 serverPort;
    quint16 proxyPortFactor;
    quint16 proxyUdpPortFactor;
    quint16 serverUdpPortFactor;
};

#endif // SETTINGS_H
