#include <gtest/gtest.h>

#include <networkutils_ipaddress.h>

TEST(IpAddress, stringToInt)
{
    networkutils::IpAddress ip("192.168.43.2");
    ASSERT_EQ(0xC0A82B02, ip.asInt());
}

TEST(IpAddress, intToString)
{
    networkutils::IpAddress ip(0xC0A82B02);
    ASSERT_EQ("192.168.43.2", ip.asString());
}

TEST(IpAddress, equality)
{
    networkutils::IpAddress ip1("192.168.43.2");
    networkutils::IpAddress ip2(0xC0A82B02);

    ASSERT_TRUE(ip1 == ip2);
    ASSERT_FALSE(ip1 != ip2);
}