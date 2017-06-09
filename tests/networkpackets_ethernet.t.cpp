#include <gtest/gtest.h>

#include <stdint.h>

#include <networkutils_packet.h>
#include <networkpackets_ethernet.h>

namespace
{

void testPacket(const networkpackets::Ethernet& ethernet)
{
    ASSERT_EQ(0, ethernet.destinationMac()[0]);
    ASSERT_EQ(1, ethernet.destinationMac()[1]);
    ASSERT_EQ(2, ethernet.destinationMac()[2]);
    ASSERT_EQ(3, ethernet.destinationMac()[3]);
    ASSERT_EQ(4, ethernet.destinationMac()[4]);
    ASSERT_EQ(5, ethernet.destinationMac()[5]);

    ASSERT_EQ(6, ethernet.sourceMac()[0]);
    ASSERT_EQ(7, ethernet.sourceMac()[1]);
    ASSERT_EQ(8, ethernet.sourceMac()[2]);
    ASSERT_EQ(9, ethernet.sourceMac()[3]);
    ASSERT_EQ(10, ethernet.sourceMac()[4]);
    ASSERT_EQ(11, ethernet.sourceMac()[5]);

    uint16_t etherType = 65535;
    ethernet.getUint16("EtherType", &etherType);
    ASSERT_EQ(0x0C0D, etherType);

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

    {
        uint8_t destinationMac[6] = {
            0, 1, 2, 3, 4, 5
        };
        ethernet.setDestinationMac(destinationMac);
    }

    {
        uint8_t sourceMac[6] = {
            6, 7, 8, 9, 10, 11
        };
        ethernet.setSourceMac(sourceMac);
    }

    {
        const uint16_t etherType = 0x0C0D;
        ethernet.setUint16("EtherType", etherType);
    }

    testPacket(ethernet);
}