#include "networkutils_ipaddress.h"

#include <sstream>
#include <stdexcept>

#include <arpa/inet.h>

#include <errno.h>

namespace networkutils
{

IpAddress::IpAddress(const std::string& ip)
    : mStringIpSet(true), mStringIp(ip), mIntIpSet(false), mIntIp(0)
{}

IpAddress::IpAddress(uint32_t ip)
    : mStringIpSet(false), mStringIp(""), mIntIpSet(true), mIntIp(ip)
{}

const std::string& IpAddress::asString() const
{
    if (!mStringIpSet)
    {
        struct sockaddr_in sa;
        sa.sin_addr.s_addr = htonl(mIntIp);

        char strIp[INET_ADDRSTRLEN];

        if (inet_ntop(AF_INET, &(sa.sin_addr), strIp, INET_ADDRSTRLEN) == 0)
        {
            std::ostringstream oss;
            oss << "inet_ntop failed, "
                << "ip = " << mIntIp << ", "
                << "errno = " << errno;
            throw std::runtime_error(oss.str());
        }

        mStringIp = strIp;
        mStringIpSet = true;
    }

    return mStringIp;
}

uint32_t IpAddress::asInt() const
{
    if (!mIntIpSet)
    {
        struct sockaddr_in sa;
        const int rc = inet_pton(AF_INET, mStringIp.c_str(), &(sa.sin_addr));
        if (rc != 1)
        {
            std::ostringstream oss;
            oss << "inet_pton failed, "
                << "ip = [" << mStringIp << "], "
                << "rc = " << rc << ", "
                << "errno = " << errno;
            throw std::runtime_error(oss.str());
        }

        mIntIp = ntohl(sa.sin_addr.s_addr);
        mIntIpSet = true;
    }

    return mIntIp;
}

bool IpAddress::operator==(const IpAddress& that) const
{
    return asInt() == that.asInt();
}

bool IpAddress::operator!=(const IpAddress& that) const
{
    return !(*this == that);
}

}