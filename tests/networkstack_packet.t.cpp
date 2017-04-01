#include <gtest/gtest.h>

#include <stdexcept>
#include <memory>

#include <networkstack_packet.h>

TEST(Packet, EmptyPacket)
{
    char data[1] = { 0 };
    networkstack::Packet packet(data, 0);
    ASSERT_EQ(0, packet.size());
}

TEST(Packet, BytesMatch)
{
    char data[5] = { 1, 2, 3, 4, 5 };
    networkstack::Packet packet(data, 5);
    ASSERT_EQ(5, packet.size());
    ASSERT_EQ(1, packet.data()[0]);
    ASSERT_EQ(2, packet.data()[1]);
    ASSERT_EQ(3, packet.data()[2]);
    ASSERT_EQ(4, packet.data()[3]);
    ASSERT_EQ(5, packet.data()[4]);
}

TEST(Packet, EmptyParent)
{
    char data[1] = { 0 };
    std::shared_ptr<networkstack::Packet> parent(new networkstack::Packet(data, 0));
    networkstack::Packet packet(parent);
    ASSERT_EQ(0, packet.size());
}

TEST(Packet, WholeParent)
{
    char data[5] = { 1, 2, 3, 4, 5 };
    std::shared_ptr<networkstack::Packet> parent(new networkstack::Packet(data, 5));
    networkstack::Packet packet(parent);
    ASSERT_EQ(5, packet.size());
    ASSERT_EQ(1, packet.data()[0]);
    ASSERT_EQ(2, packet.data()[1]);
    ASSERT_EQ(3, packet.data()[2]);
    ASSERT_EQ(4, packet.data()[3]);
    ASSERT_EQ(5, packet.data()[4]);
}

TEST(Packet, SubParent)
{
    char data[5] = { 1, 2, 3, 4, 5 };
    std::shared_ptr<networkstack::Packet> parent(new networkstack::Packet(data, 5));
    networkstack::Packet packet(parent, 1, 3);
    ASSERT_EQ(3, packet.size());
    ASSERT_EQ(2, packet.data()[0]);
    ASSERT_EQ(3, packet.data()[1]);
    ASSERT_EQ(4, packet.data()[2]);
}

TEST(Packet, OutOfBounds)
{
    char data[5] = { 1, 2, 3, 4, 5 };
    std::shared_ptr<networkstack::Packet> parent(new networkstack::Packet(data, 5));
    ASSERT_THROW(networkstack::Packet(parent, 6, 0), std::runtime_error);
    ASSERT_THROW(networkstack::Packet(parent, 0, 6), std::runtime_error);
}