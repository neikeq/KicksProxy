#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <QObject>

class Cryptography
{
public:
    static QByteArray xorBytes(const QByteArray &buffer);
};

#endif // CRYPTOGRAPHY_H
