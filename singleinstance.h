#ifndef SINGLEINSTANCE_H
#define SINGLEINSTANCE_H

#include <QLocalServer>
#include <QLocalSocket>
#include <QObject>

class SingleInstance : public QObject
{
    Q_OBJECT
public:
    explicit SingleInstance(QObject *parent = 0);

    /**
     * @brief Listen for connections
     * @param name
     */
    void listen(const QString &name);

    /**
     * @brief Check if an instance is already running
     * @param name
     * @return
     */
    bool instanceExists(const QString &name, const QStringList &arguments);
signals:

public slots:
    void newConnection();
    void readyRead();

private:
    QLocalSocket* socket;
    QLocalServer server;
};

#endif // SINGLEINSTANCE_H
