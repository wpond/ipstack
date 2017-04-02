#include <gtest/gtest.h>

#include <stdexcept>
#include <queue>

#include <tests_adapter.h>

#include <networkadapter_adapter.h>
#include <networkutils_packet.h>

TEST(Adapter, Create)
{
    const char hardwareAddress[6] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    tests::Adapter adapter("interface", hardwareAddress);
    ASSERT_EQ("interface", adapter.interface());
    ASSERT_EQ(0x01, adapter.hardwareAddress()[0]);
    ASSERT_EQ(0x02, adapter.hardwareAddress()[1]);
    ASSERT_EQ(0x03, adapter.hardwareAddress()[2]);
    ASSERT_EQ(0x04, adapter.hardwareAddress()[3]);
    ASSERT_EQ(0x05, adapter.hardwareAddress()[4]);
    ASSERT_EQ(0x06, adapter.hardwareAddress()[5]);
}

TEST(Adapter, AttachNull)
{
    const char hardwareAddress[6] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    tests::Adapter adapter("interface", hardwareAddress);
    ASSERT_THROW(adapter.attach(NULL), std::runtime_error);
}

TEST(Adapter, DetatchNull)
{
    const char hardwareAddress[6] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    tests::Adapter adapter("interface", hardwareAddress);
    ASSERT_THROW(adapter.attach(NULL), std::runtime_error);
}

TEST(Adapter, emptySentQueue)
{
    const char hardwareAddress[6] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    tests::Adapter adapter("interface", hardwareAddress);
    ASSERT_FALSE(adapter.testSent());
}

TEST(Adapter, SendToSent)
{
    const char hardwareAddress[6] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    tests::Adapter adapter("interface", hardwareAddress);

    const char data[2] = { 0x01, 0x02 };
    std::shared_ptr<networkutils::Packet> packet(new networkutils::Packet(data, 2));
    adapter.send(packet);

    std::shared_ptr<networkutils::Packet> received = adapter.testSent();

    ASSERT_EQ(packet->size(), received->size());
    ASSERT_EQ(packet->data()[0], received->data()[0]);
    ASSERT_EQ(packet->data()[1], received->data()[1]);
    ASSERT_FALSE(adapter.testSent());
}

TEST(Adapter, ReceiveOne)
{
    const char hardwareAddress[6] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    tests::Adapter adapter("interface", hardwareAddress);

    tests::Observer observer;
    adapter.attach(&observer);
    
    const char data[2] = { 0x01, 0x02 };
    std::shared_ptr<const networkutils::Packet> expected(new networkutils::Packet(data, 2));
    adapter.testReceive(expected);

    std::shared_ptr<const networkutils::Packet> actual = observer.received();
    ASSERT_EQ(2, actual->size());
    ASSERT_EQ(1, actual->data()[0]);
    ASSERT_EQ(2, actual->data()[1]);

    ASSERT_FALSE(observer.received());
}