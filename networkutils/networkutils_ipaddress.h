#ifndef NETWORKUTILS_IPADDRESS_H
#define NETWORKUTILS_IPADDRESS_H

#include <string>
#include <cstdint>
#include <ostream>

namespace networkutils
{

class IpAddress
{
public:
    IpAddress(const std::string& ip);
    IpAddress(uint32_t ip);

    const std::string& asString() const;
    uint32_t asInt() const;

    bool operator==(const IpAddress& that) const;
    bool operator!=(const IpAddress& that) const;

private:
    mutable bool mStringIpSet;
    mutable std::string mStringIp;
    mutable bool mIntIpSet;
    mutable uint32_t mIntIp;
};

inline std::ostream& operator<<(std::ostream& stream, const IpAddress& ip)
{
    return stream << ip.asString() << " (" << ip.asInt() << ")";
}

}

#endif