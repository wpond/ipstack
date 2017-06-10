#include <gtest/gtest.h>

#include <stdexcept>

#include <networkstack_arptable.h>

TEST(ArpTable, constructor)
{
    {
        networkstack::ArpTable(0);
    }

    {
        networkstack::ArpTable(255);
    }

    {
        networkstack::ArpTable(-1);
    }
}

TEST(ArpTable, nullPointers)
{
    uint8_t hwAddress[6] = { 0 };
    uint8_t ipAddress[4] = { 0 };

    networkstack::ArpTable table(1);

    ASSERT_THROW(table.update(0, ipAddress), std::runtime_error);
    ASSERT_THROW(table.update(hwAddress, 0), std::runtime_error);

    ASSERT_THROW(table.lookupHardwareAddress(0, ipAddress), std::runtime_error);
    ASSERT_THROW(table.lookupHardwareAddress(hwAddress, 0), std::runtime_error);

    ASSERT_THROW(table.lookupIpAddress(0, ipAddress), std::runtime_error);
    ASSERT_THROW(table.lookupIpAddress(hwAddress, 0), std::runtime_error);
}

TEST(ArpTable, insertFull)
{
    networkstack::ArpTable table(1);

    {
        const uint8_t hwAddress[6] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x01
        };
        const uint8_t ipAddress[4] = {
            0x00, 0x00, 0x00, 0x01
        };

        ASSERT_TRUE(table.update(hwAddress, ipAddress));
    }

    {
        const uint8_t hwAddress[6] = { 0 };
        const uint8_t ipAddress[4] = { 0 };

        ASSERT_THROW(table.update(hwAddress, ipAddress), std::runtime_error);
    }
}

TEST(ArpTable, updateFull)
{
    networkstack::ArpTable table(1);

    const uint8_t hwAddress[6] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01
    };
    const uint8_t ipAddress[4] = {
        0x00, 0x00, 0x00, 0x01
    };

    ASSERT_TRUE(table.update(hwAddress, ipAddress));
    ASSERT_FALSE(table.update(hwAddress, ipAddress));
}

TEST(ArpTable, update)
{
    networkstack::ArpTable table(10);

    {
        const uint8_t hwAddress[6] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x01
        };
        const uint8_t ipAddress[4] = {
            0x00, 0x00, 0x00, 0x01
        };

        ASSERT_TRUE(table.update(hwAddress, ipAddress));
        ASSERT_FALSE(table.update(hwAddress, ipAddress));
    }

    {
        const uint8_t hwAddress[6] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x02
        };
        const uint8_t ipAddress[4] = {
            0x00, 0x00, 0x00, 0x02
        };

        ASSERT_TRUE(table.update(hwAddress, ipAddress));
        ASSERT_FALSE(table.update(hwAddress, ipAddress));
    }

    {
        const uint8_t hwAddress[6] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x01
        };
        const uint8_t ipAddress[4] = {
            0x00, 0x00, 0x00, 0x03
        };

        ASSERT_FALSE(table.update(hwAddress, ipAddress));
    }

    {
        const uint8_t hwAddress[6] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x01
        };
        uint8_t ipAddress[4] = { 0 };

        ASSERT_TRUE(table.lookupIpAddress(hwAddress, ipAddress));

        ASSERT_EQ(0x00, ipAddress[0]);
        ASSERT_EQ(0x00, ipAddress[1]);
        ASSERT_EQ(0x00, ipAddress[2]);
        ASSERT_EQ(0x03, ipAddress[3]);
    }
}

TEST(ArpTable, missingHardwareAddress)
{
    networkstack::ArpTable table(10);

    {
        const uint8_t hwAddress[6] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x01
        };
        const uint8_t ipAddress[4] = {
            0x00, 0x00, 0x00, 0x01
        };

        ASSERT_TRUE(table.update(hwAddress, ipAddress));
    }

    {
        const uint8_t hwAddress[6] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x02
        };
        uint8_t ipAddress[4] = { 0 };

        ASSERT_FALSE(table.lookupHardwareAddress(hwAddress, ipAddress));
    }
}

TEST(ArpTable, findHardwareAddress)
{
    networkstack::ArpTable table(10);

    const uint8_t hwAddress[6] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01
    };
    const uint8_t ipAddress[4] = {
        0x00, 0x00, 0x00, 0x01
    };

    ASSERT_TRUE(table.update(hwAddress, ipAddress));
    
    uint8_t foundAddress[6];
    ASSERT_TRUE(table.lookupHardwareAddress(ipAddress, foundAddress));
    for (int i = 0; i < 6; ++i)
    {
        ASSERT_EQ(hwAddress[i], foundAddress[i]);
    }
}

TEST(ArpTable, missingIpAddress)
{
    networkstack::ArpTable table(10);

    {
        const uint8_t hwAddress[6] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x01
        };
        const uint8_t ipAddress[4] = {
            0x00, 0x00, 0x00, 0x01
        };

        ASSERT_TRUE(table.update(hwAddress, ipAddress));
    }

    {
        uint8_t hwAddress[6] = { 0 };
        const uint8_t ipAddress[4] = {
            0x00, 0x00, 0x00, 0x02
        };

        ASSERT_FALSE(table.lookupIpAddress(ipAddress, hwAddress));
    }
}

TEST(ArpTable, findIpAddress)
{
    networkstack::ArpTable table(10);

    const uint8_t hwAddress[6] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01
    };
    const uint8_t ipAddress[4] = {
        0x00, 0x00, 0x00, 0x01
    };

    ASSERT_TRUE(table.update(hwAddress, ipAddress));
    
    uint8_t foundAddress[4];
    ASSERT_TRUE(table.lookupIpAddress(hwAddress, foundAddress));
    for (int i = 0; i < 4; ++i)
    {
        ASSERT_EQ(ipAddress[i], foundAddress[i]);
    }
}
