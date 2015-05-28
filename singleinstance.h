#ifndef SINGLEINSTANCE_H
#define SINGLEINSTANCE_H

#include <QObject>
#include <QDebug>
#include <QLocalServer>
#include <QLocalSocket>

class SingleInstance : public QObject
{
    Q_OBJECT
public:
    explicit SingleInstance(QObject *parent = 0);

    /**
     * @brief Listen for connections
     * @param name
     */
    void listen(QString name);

    /**
     * @brief Check if an instance is already running
     * @param name
     * @return
     */
    bool instanceExists(QString name);
signals:

public slots:
    /**
     * @brief Called when a new connection is opened
     */
    void newConnection();

    /**
     * @brief Called when new data is available to read
     */
    void readyRead();

private:
    QLocalSocket* socket;
    QLocalServer server;

};

#endif // SINGLEINSTANCE_H
