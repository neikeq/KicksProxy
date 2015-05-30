#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings
{
public:
    static const quint32 HEADER_SIZE;
    static const quint32 BODY_SIZE_INDEX;
    static const quint8 XOR_KEY;

    inline const QString& getServerAddress() const { return serverAddress; }
    inline int getServerPort() const { return serverPort; }
    inline int getProxyPortFactor() const { return proxyPortFactor; }

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
    qint16 serverPort;
    qint16 proxyPortFactor;
};

#endif // SETTINGS_H
