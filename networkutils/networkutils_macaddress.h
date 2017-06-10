#ifndef NETWORKUTILS_MACADDRESS_H
#define NETWORKUTILS_MACADDRESS_H

#include <ostream>
#include <cstdint>

#include "networkutils_byteoutputter.h"

namespace networkutils
{

class MacAddress
{
public:
    MacAddress();
    MacAddress(uint8_t* value);
    MacAddress(
        uint8_t byte1,
        uint8_t byte2,
        uint8_t byte3,
        uint8_t byte4,
        uint8_t byte5,
        uint8_t byte6);

    MacAddress(const MacAddress& that);
    MacAddress& operator=(const MacAddress& rhs);

    uint8_t* value();
    const uint8_t* value() const;

    uint8_t size() const;

    bool operator==(const MacAddress& rhs) const;
private:
    uint8_t mAddress[6];
};

inline std::ostream& operator<<(std::ostream& stream, const MacAddress& mac)
{
    return stream << ByteOutputter(mac.value(), 6);
}

}

#endif