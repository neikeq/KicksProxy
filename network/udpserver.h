#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>

#define PLAYER_INFO_MAP QHash<quint16, PlayerInfo>

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(quint16 serverId, const QString &serverAddress, QObject *parent = 0);

    void writeDatagram(const QByteArray &datagram, const QHostAddress &address, quint16 port);
signals:
    void setPlayerInfo(quint32 mapId, quint32 playerId, QString address, quint16 port);
    void clearPlayerMap(quint32 mapId);
    void removePlayer(quint32 mapId, quint32 playerId);

public slots:
    void readyRead();
    void onClearPlayerMap(quint32 mapId);
    void onRemovePlayer(quint32 mapId, quint32 playerId);
    void onSetPlayerInfo(quint32 mapId, quint32 playerId, QString address, quint16 port);
private:
    QUdpSocket *socket;

    QHostAddress serverAddress;
    quint16 serverPort;
    quint16 bindPort;

    struct PlayerInfo {
        QHostAddress address;
        quint16 port;
    };

    QHash<quint16, PLAYER_INFO_MAP> playerMaps;
};

#endif // UDPSERVER_H
