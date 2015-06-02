#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings
{
public:
    static const quint32 BODY_SIZE_INDEX;
    static const quint32 HEADER_SIZE;
    static const QString LOCALHOST;
    static const quint16 MAIN_SERVER_ID;
    static const quint16 UDP_PORT_FACTOR;
    static const quint8 XOR_KEY;

    inline const QString& getServerAddress() const { return serverAddress; }
    inline int getServerPort() const { return serverPort; }
    inline int getProxyPortFactor() const { return proxyPortFactor; }
    inline int getServerUdpPortFactor() const { return serverUdpPortFactor; }

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

    QString serverAddress;
    quint16 serverPort;
    quint16 proxyPortFactor;
    quint16 serverUdpPortFactor;
};

#endif // SETTINGS_H
