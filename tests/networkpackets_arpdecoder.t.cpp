#include <gtest/gtest.h>

#include <arpa/inet.h>

#include <stdexcept>

#include <networkpackets_arpdecoder.h>

void testHeaders(const char* data, const networkpackets::ArpDecoder& decoder)
{
    ASSERT_EQ(ntohs(*data), decoder.hardwareType());
    ASSERT_EQ(ntohs(*(data + 2)), decoder.protocolType());
    ASSERT_EQ(0x05, decoder.hardwareSize());
    ASSERT_EQ(0x06, decoder.protocolSize());
    ASSERT_EQ(ntohs(*(data + 6)), decoder.opCode());
}

TEST(ArpDecoder, emptyPacket)
{
    std::shared_ptr<networkutils::Packet> packet;
    ASSERT_THROW(networkpackets::ArpDecoder decoder(packet), std::runtime_error);
}

TEST(ArpDecoder, emptyPayload)
{
    const char data[8] = {
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
    const char data[12] = {
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
