#include "cryptography.h"

#include "constants.h"

QByteArray Cryptography::xorBytes(const QByteArray &buffer)
{
    QByteArray result;

    for (int i = 0; i < buffer.size(); i++) {
        result.insert(i, i < 12 ? buffer[i] : (char)buffer[i] ^ Constants::XOR_KEY);
    }

    return result;
}
