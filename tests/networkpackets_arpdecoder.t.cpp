#include <gtest/gtest.h>

#include <arpa/inet.h>

#include <stdexcept>
#include <cstdint>

#include <networkpackets_arpdecoder.h>

void testHeaders(const uint8_t* data, const networkpackets::ArpDecoder& decoder)
{
    ASSERT_EQ(0x0102, decoder.hardwareType());
    ASSERT_EQ(0x0304, decoder.protocolType());
    ASSERT_EQ(0x05, decoder.hardwareSize());
    ASSERT_EQ(0x06, decoder.protocolSize());
    ASSERT_EQ(0x0708, decoder.opCode());
}

TEST(ArpDecoder, emptyPacket)
{
    std::shared_ptr<networkutils::Packet> packet;
    ASSERT_THROW(networkpackets::ArpDecoder decoder(packet), std::runtime_error);
}

TEST(ArpDecoder, emptyPayload)
{
    const uint8_t data[8] = {
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08
    };
    std::shared_ptr<networkutils::Packet> packet(new networkutils::Packet(data, sizeof(data)));
    networkpackets::ArpDecoder decoder(packet);
    testHeaders(data, decoder);
    ASSERT_EQ(0, decoder.payload()->size());
}

TEST(ArpDecoder, payload)
{
    const uint8_t data[12] = {
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08,
        0x09, 0x10, 0x11, 0x12
    };
    std::shared_ptr<networkutils::Packet> packet(new networkutils::Packet(data, sizeof(data)));
    networkpackets::ArpDecoder decoder(packet);
    testHeaders(data, decoder);
    ASSERT_EQ(4, decoder.payload()->size());
    ASSERT_EQ(0x09, *(decoder.payload()->data() + 0));
    ASSERT_EQ(0x10, *(decoder.payload()->data() + 1));
    ASSERT_EQ(0x11, *(decoder.payload()->data() + 2));
    ASSERT_EQ(0x12, *(decoder.payload()->data() + 3));
}

TEST(ArpDecoder, realScenario)
{
    const uint8_t data[] = {
        0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01,
        0x8e, 0xab, 0x46, 0x2d, 0x13, 0x5d, 0xc0, 0xa8,
        0x2b, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xc0, 0xa8, 0x2b, 0x02
    };

    std::shared_ptr<networkutils::Packet> packet(new networkutils::Packet(data, sizeof(data)));
    networkpackets::ArpDecoder decoder(packet);

    ASSERT_EQ(0x0001, decoder.hardwareType());
    ASSERT_EQ(0x0800, decoder.protocolType());
    ASSERT_EQ(0x06, decoder.hardwareSize());
    ASSERT_EQ(0x04, decoder.protocolSize());
    ASSERT_EQ(0x0001, decoder.opCode());
}