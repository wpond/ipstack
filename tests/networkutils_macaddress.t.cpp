#include <gtest/gtest.h>

#include <cstdint>

#include "networkutils_macaddress.h"

TEST(MacAddress, defaultConstructor)
{
    networkutils::MacAddress addr;
    
    ASSERT_EQ(0x00, addr.value()[0]);
    ASSERT_EQ(0x00, addr.value()[1]);
    ASSERT_EQ(0x00, addr.value()[2]);
    ASSERT_EQ(0x00, addr.value()[3]);
    ASSERT_EQ(0x00, addr.value()[4]);
    ASSERT_EQ(0x00, addr.value()[5]);
}

TEST(MacAddress, initialiserList)
{
    networkutils::MacAddress addr = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05
    };

    ASSERT_EQ(0x00, addr.value()[0]);
    ASSERT_EQ(0x01, addr.value()[1]);
    ASSERT_EQ(0x02, addr.value()[2]);
    ASSERT_EQ(0x03, addr.value()[3]);
    ASSERT_EQ(0x04, addr.value()[4]);
    ASSERT_EQ(0x05, addr.value()[5]);
}

TEST(MacAddress, copyConstructor)
{
    networkutils::MacAddress addr1 = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05
    };

    networkutils::MacAddress addr2(addr1);

    ASSERT_EQ(0x00, addr2.value()[0]);
    ASSERT_EQ(0x01, addr2.value()[1]);
    ASSERT_EQ(0x02, addr2.value()[2]);
    ASSERT_EQ(0x03, addr2.value()[3]);
    ASSERT_EQ(0x04, addr2.value()[4]);
    ASSERT_EQ(0x05, addr2.value()[5]);   
}

TEST(MacAddress, constructor)
{
    uint8_t rawAddr[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05
    };

    networkutils::MacAddress addr(rawAddr);

    ASSERT_EQ(0x00, addr.value()[0]);
    ASSERT_EQ(0x01, addr.value()[1]);
    ASSERT_EQ(0x02, addr.value()[2]);
    ASSERT_EQ(0x03, addr.value()[3]);
    ASSERT_EQ(0x04, addr.value()[4]);
    ASSERT_EQ(0x05, addr.value()[5]);
}

TEST(MacAddress, assignment)
{
    networkutils::MacAddress addr1 = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05
    };

    networkutils::MacAddress addr2 = {
        0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B
    };

    addr2 = addr1;

    ASSERT_EQ(0x00, addr1.value()[0]);
    ASSERT_EQ(0x01, addr1.value()[1]);
    ASSERT_EQ(0x02, addr1.value()[2]);
    ASSERT_EQ(0x03, addr1.value()[3]);
    ASSERT_EQ(0x04, addr1.value()[4]);
    ASSERT_EQ(0x05, addr1.value()[5]);

    ASSERT_EQ(0x00, addr2.value()[0]);
    ASSERT_EQ(0x01, addr2.value()[1]);
    ASSERT_EQ(0x02, addr2.value()[2]);
    ASSERT_EQ(0x03, addr2.value()[3]);
    ASSERT_EQ(0x04, addr2.value()[4]);
    ASSERT_EQ(0x05, addr2.value()[5]);
}

TEST(MacAddress, equality)
{
    networkutils::MacAddress addr1 = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05
    };

    networkutils::MacAddress addr2 = {
        0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B
    };

    ASSERT_FALSE(addr1 == addr2);

    addr1 = addr2;

    ASSERT_TRUE(addr1 == addr2);
}