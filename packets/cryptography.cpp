#include "packets/cryptography.h"

#include "settings.h"

QByteArray Cryptography::xorBytes(const QByteArray &buffer)
{
    QByteArray result;

    for (int i = 0; i < buffer.size(); i++) {
        result.insert(i, i < 12 ? buffer[i] : (char)buffer[i] ^ Settings::XOR_KEY);
    }

    return result;
}
