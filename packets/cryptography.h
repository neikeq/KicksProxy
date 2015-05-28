#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <QObject>

class Cryptography
{
public:
    /**
     * @brief Xor each byte of the specified byte array by the xor key
     * @param The byte array
     * @return A xored copy of the specified byte array
     */
    static QByteArray xorBytes(const QByteArray &buffer);
};

#endif // CRYPTOGRAPHY_H
