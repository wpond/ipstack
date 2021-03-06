#include <gtest/gtest.h>

#include <cstdint>

#include <networkutils_packet.h>
#include <networkpackets_ethernet.h>

namespace
{

void testPacket(const networkpackets::Ethernet& ethernet)
{
    {
        const networkutils::MacAddress macAddress = {
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05
        };
        ASSERT_EQ(macAddress, ethernet.getMacAddress("DestinationMac"));
    }

    {
        const networkutils::MacAddress macAddress = {
            0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B
        };
        ASSERT_EQ(macAddress, ethernet.getMacAddress("SourceMac"));
    }

    ASSERT_EQ(0x0C0D, ethernet.getUint16("EtherType"));

    std::shared_ptr<networkutils::Packet> payload = ethernet.getPayload("Payload");
    ASSERT_EQ(6, payload->size());

    ASSERT_EQ(14, payload->data()[0]);
    ASSERT_EQ(15, payload->data()[1]);
    ASSERT_EQ(16, payload->data()[2]);
    ASSERT_EQ(17, payload->data()[3]);
    ASSERT_EQ(18, payload->data()[4]);
    ASSERT_EQ(19, payload->data()[5]);
}

}

TEST(Ethernet, fromFullPacket)
{
    uint8_t rawPacket[20];

    for (unsigned int i = 0; i < sizeof(rawPacket); ++i)
    {
        rawPacket[i] = i;
    }

    std::shared_ptr<networkutils::Packet> packet(new networkutils::Packet(rawPacket, sizeof(rawPacket)));
    networkpackets::Ethernet ethernet = networkpackets::Ethernet::fromFullPacket(packet);

    testPacket(ethernet);
}

TEST(Ethernet, fromPayload)
{
    uint8_t rawPayload[6];

    rawPayload[0] = 14;
    rawPayload[1] = 15;
    rawPayload[2] = 16;
    rawPayload[3] = 17;
    rawPayload[4] = 18;
    rawPayload[5] = 19;

    std::shared_ptr<networkutils::Packet> payload(new networkutils::Packet(rawPayload, sizeof(rawPayload)));
    networkpackets::Ethernet ethernet = networkpackets::Ethernet::fromPayload(payload);

    ethernet.setMacAddress("DestinationMac", { 0, 1, 2, 3, 4, 5 });
    ethernet.setMacAddress("SourceMac", { 6, 7, 8, 9, 10, 11 });

    {
        const uint16_t etherType = 0x0C0D;
        ethernet.setUint16("EtherType", etherType);
    }

    testPacket(ethernet);
}