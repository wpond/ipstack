#include "networkpackets_arp.h"

#include <cstring>

namespace networkpackets
{

namespace
{

const int HARDWARE_TYPE_OFFSET = 0;
const int PROTOCOL_TYPE_OFFSET = 2;
const int HARDWARE_SIZE_OFFSET = 4;
const int PROTOCOL_SIZE_OFFSET = 5;
const int OPCODE_OFFSET = 6;
const int SOURCE_MAC_OFFSET = 8;
const int SOURCE_IP_OFFSET = 14;
const int DESTINATION_MAC_OFFSET = 18;
const int DESTINATION_IP_OFFSET = 24;

const int SOURCE_MAC_SIZE = 6;
const int DESTINATION_MAC_SIZE = 6;
const int PACKET_SIZE = 28;

}

Arp Arp::fromPayload(std::shared_ptr<networkutils::Packet> payload)
{
    if (!payload)
    {
        throw std::runtime_error("Passed NULL payload to fromPayload");
    }

    const uint32_t size = PACKET_SIZE + payload->size();
    uint8_t rawPacket[size];

    memset(rawPacket, 0, size);
    memcpy(rawPacket + PACKET_SIZE, payload->data(), payload->size());

    std::shared_ptr<networkutils::Packet> packet(new networkutils::Packet(rawPacket, size));
    return Arp(packet);
}

Arp Arp::fromFullPacket(std::shared_ptr<networkutils::Packet> packet)
{
    if (!packet)
    {
        throw std::runtime_error("Passed NULL packet to fromFullPacket");
    }

    return Arp(packet);
}

Arp::Arp(std::shared_ptr<networkutils::Packet> packet)
    : GenericInterface(packet)
{
    addField("HardwareType", GenericInterface::UINT16, HARDWARE_TYPE_OFFSET);
    addField("ProtocolType", GenericInterface::UINT16, PROTOCOL_TYPE_OFFSET);
    addField("HardwareSize", GenericInterface::UINT8, HARDWARE_SIZE_OFFSET);
    addField("ProtocolSize", GenericInterface::UINT8, PROTOCOL_SIZE_OFFSET);
    addField("OpCode", GenericInterface::UINT16, OPCODE_OFFSET);
    addField("SourceIP", GenericInterface::UINT32, SOURCE_IP_OFFSET);
    addField("DestinationIP", GenericInterface::UINT32, DESTINATION_IP_OFFSET);
    addField("SourceMac", GenericInterface::MACADDRESS, SOURCE_MAC_OFFSET);
    addField("DestinationMac", GenericInterface::MACADDRESS, DESTINATION_MAC_OFFSET);
}

}