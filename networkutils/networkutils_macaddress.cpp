#include "networkutils_macaddress.h"

#include <cstring>

namespace networkutils
{

MacAddress::MacAddress()
{
    memset(mAddress, 0, sizeof(mAddress));
}

MacAddress::MacAddress(uint8_t* value)
{
    memcpy(mAddress, value, sizeof(mAddress));
}

MacAddress::MacAddress(
    uint8_t byte1,
    uint8_t byte2,
    uint8_t byte3,
    uint8_t byte4,
    uint8_t byte5,
    uint8_t byte6)
{
    mAddress[0] = byte1;
    mAddress[1] = byte2;
    mAddress[2] = byte3;
    mAddress[3] = byte4;
    mAddress[4] = byte5;
    mAddress[5] = byte6;
}

MacAddress::MacAddress(const MacAddress& that)
{
    memcpy(mAddress, that.mAddress, sizeof(mAddress));
}

MacAddress& MacAddress::operator=(const MacAddress& rhs)
{
    memcpy(mAddress, rhs.mAddress, sizeof(mAddress));
    return *this;
}

uint8_t* MacAddress::value()
{
    return mAddress;
}

const uint8_t* MacAddress::value() const
{
    return mAddress;
}

uint8_t MacAddress::size() const
{
    return 6;
}

bool MacAddress::operator==(const MacAddress& rhs) const
{
    return memcmp(mAddress, rhs.mAddress, sizeof(mAddress)) == 0;
}

}