#include <gtest/gtest.h>

#include <stdexcept>
#include <memory>
#include <cstdint>

#include <networkutils_packet.h>

TEST(Packet, EmptyPacket)
{
    uint8_t data[1] = { 0 };
    networkutils::Packet packet(data, 0);
    ASSERT_EQ(0, packet.size());
}

TEST(Packet, BytesMatch)
{
    uint8_t data[5] = { 1, 2, 3, 4, 5 };
    networkutils::Packet packet(data, 5);
    ASSERT_EQ(5, packet.size());
    ASSERT_EQ(1, packet.data()[0]);
    ASSERT_EQ(2, packet.data()[1]);
    ASSERT_EQ(3, packet.data()[2]);
    ASSERT_EQ(4, packet.data()[3]);
    ASSERT_EQ(5, packet.data()[4]);
}

TEST(Packet, EmptyParent)
{
    uint8_t data[1] = { 0 };
    std::shared_ptr<networkutils::Packet> parent(new networkutils::Packet(data, 0));
    networkutils::Packet packet(parent);
    ASSERT_EQ(0, packet.size());
}

TEST(Packet, WholeParent)
{
    uint8_t data[5] = { 1, 2, 3, 4, 5 };
    std::shared_ptr<networkutils::Packet> parent(new networkutils::Packet(data, 5));
    networkutils::Packet packet(parent);
    ASSERT_EQ(5, packet.size());
    ASSERT_EQ(1, packet.data()[0]);
    ASSERT_EQ(2, packet.data()[1]);
    ASSERT_EQ(3, packet.data()[2]);
    ASSERT_EQ(4, packet.data()[3]);
    ASSERT_EQ(5, packet.data()[4]);
}

TEST(Packet, SubParent)
{
    uint8_t data[5] = { 1, 2, 3, 4, 5 };
    std::shared_ptr<networkutils::Packet> parent(new networkutils::Packet(data, 5));
    networkutils::Packet packet(parent, 1, 3);
    ASSERT_EQ(3, packet.size());
    ASSERT_EQ(2, packet.data()[0]);
    ASSERT_EQ(3, packet.data()[1]);
    ASSERT_EQ(4, packet.data()[2]);
}

TEST(Packet, OutOfBounds)
{
    uint8_t data[5] = { 1, 2, 3, 4, 5 };
    std::shared_ptr<networkutils::Packet> parent(new networkutils::Packet(data, 5));
    ASSERT_THROW(networkutils::Packet(parent, 6, 0), std::runtime_error);
    ASSERT_THROW(networkutils::Packet(parent, 0, 6), std::runtime_error);
}
