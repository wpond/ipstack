#include <gtest/gtest.h>

#include <networkpackets_arpfactory.h>

#include <networkutils_packet.h>

#include <memory>
#include <cstdint>

#include <arpa/inet.h>

namespace
{

const uint32_t EMPTY_SIZE = 8;

const uint32_t HW_TYPE_OFFSET = 0;
const uint32_t PROTOCOL_TYPE_OFFSET = 2;
const uint32_t HW_SIZE_OFFSET = 4;
const uint32_t PROTOCOL_SIZE_OFFSET = 5;
const uint32_t OPCODE_OFFSET = 6;
const uint32_t DATA_OFFSET = 8;

}

TEST(ArpFactory, defaultSize)
{
    networkpackets::ArpFactory factory(0x1234, 0, 0);
    std::shared_ptr<networkutils::Packet> packet = factory.getPacket();
    ASSERT_EQ(EMPTY_SIZE, packet->size());
}

TEST(ArpFactory, defaultHardwareType)
{
    networkpackets::ArpFactory factory(0x1234, 0, 0);
    std::shared_ptr<networkutils::Packet> packet = factory.getPacket();
    const uint8_t* type = packet->data() + HW_TYPE_OFFSET;
    ASSERT_EQ(0x00, type[0]);
    ASSERT_EQ(0x01, type[1]);
}

TEST(ArpFactory, hardwareType)
{
    networkpackets::ArpFactory factory(0x1234, 0, 0);
    factory.setHardwareType(0x0102);
    std::shared_ptr<networkutils::Packet> packet = factory.getPacket();
    const uint8_t* type = packet->data() + HW_TYPE_OFFSET;
    ASSERT_EQ(0x01, type[0]);
    ASSERT_EQ(0x02, type[1]);
}

TEST(ArpFactory, defaultProtocolType)
{
    networkpackets::ArpFactory factory(0x1234, 0, 0);
    std::shared_ptr<networkutils::Packet> packet = factory.getPacket();
    const uint8_t* type = packet->data() + PROTOCOL_TYPE_OFFSET;
    ASSERT_EQ(0x08, type[0]);
    ASSERT_EQ(0x00, type[1]);
}

TEST(ArpFactory, protocolType)
{
    networkpackets::ArpFactory factory(0x1234, 0, 0);
    factory.setProtocolType(0x0102);
    std::shared_ptr<networkutils::Packet> packet = factory.getPacket();
    const uint8_t* type = packet->data() + PROTOCOL_TYPE_OFFSET;
    ASSERT_EQ(0x01, type[0]);
    ASSERT_EQ(0x02, type[1]);
}

TEST(ArpFactory, defaultHardwareSize)
{
    networkpackets::ArpFactory factory(0x1234, 0, 0);
    std::shared_ptr<networkutils::Packet> packet = factory.getPacket();
    const uint8_t* size = packet->data() + HW_SIZE_OFFSET;
    ASSERT_EQ(0x06, size[0]);
}

TEST(ArpFactory, hardwareSize)
{
    networkpackets::ArpFactory factory(0x1234, 0, 0);
    factory.setHardwareSize(2);
    std::shared_ptr<networkutils::Packet> packet = factory.getPacket();
    const uint8_t* size = packet->data() + HW_SIZE_OFFSET;
    ASSERT_EQ(0x02, size[0]);
}

TEST(ArpFactory, defaultProtocolSize)
{
    networkpackets::ArpFactory factory(0x1234, 0, 0);
    std::shared_ptr<networkutils::Packet> packet = factory.getPacket();
    const uint8_t* size = packet->data() + PROTOCOL_SIZE_OFFSET;
    ASSERT_EQ(0x04, size[0]);
}

TEST(ArpFactory, protocolSize)
{
    networkpackets::ArpFactory factory(0x1234, 0, 0);
    factory.setProtocolSize(2);
    std::shared_ptr<networkutils::Packet> packet = factory.getPacket();
    const uint8_t* size = packet->data() + PROTOCOL_SIZE_OFFSET;
    ASSERT_EQ(0x02, size[0]);
}

TEST(ArpFactory, opCode)
{
    networkpackets::ArpFactory factory(0x1234, 0, 0);
    std::shared_ptr<networkutils::Packet> packet = factory.getPacket();
    const uint8_t* type = packet->data() + OPCODE_OFFSET;
    ASSERT_EQ(0x12, type[0]);
    ASSERT_EQ(0x34, type[1]);
}

TEST(ArpFactory, payload)
{
    const uint8_t data[3] = { 0x01, 0x02, 0x03 };
    networkpackets::ArpFactory factory(0x1234, data, sizeof(data));
    std::shared_ptr<networkutils::Packet> packet = factory.getPacket();
    ASSERT_EQ(EMPTY_SIZE + sizeof(data), packet->size());
    const uint8_t* payload = packet->data() + EMPTY_SIZE;
    ASSERT_EQ(data[0], payload[0]);
    ASSERT_EQ(data[1], payload[1]);
    ASSERT_EQ(data[2], payload[2]);
}
