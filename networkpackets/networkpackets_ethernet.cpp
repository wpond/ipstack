#include <networkpackets_ethernet.h>

#include <cstring>

namespace networkpackets
{

namespace
{

const int DMAC_OFFSET = 0;
const int SMAC_OFFSET = 6;
const int ETHERTYPE_OFFSET = 12;
const int PAYLOAD_OFFSET = 14;

const int DMAC_SIZE = 6;
const int SMAC_SIZE = 6;

const int HEADER_SIZE = 14;

}

Ethernet Ethernet::fromPayload(std::shared_ptr<networkutils::Packet> payload)
{
    if (!payload)
    {
        throw std::runtime_error("Passed NULL payload to fromPayload");
    }

    const uint32_t size = HEADER_SIZE + payload->size();
    uint8_t rawPacket[size];

    memset(rawPacket, 0, size);
    memcpy(rawPacket + HEADER_SIZE, payload->data(), payload->size());

    std::shared_ptr<networkutils::Packet> packet(new networkutils::Packet(rawPacket, size));
    return Ethernet(packet);
}

Ethernet Ethernet::fromFullPacket(std::shared_ptr<networkutils::Packet> packet)
{
    if (!packet)
    {
        throw std::runtime_error("Passed NULL packet to fromFullPacket");
    }

    return Ethernet(packet);
}

Ethernet::Ethernet(std::shared_ptr<networkutils::Packet> packet)
    : GenericInterface(packet)
{
    addField("EtherType", GenericInterface::UINT16, ETHERTYPE_OFFSET);
    addField("Payload", GenericInterface::PAYLOAD, PAYLOAD_OFFSET);
}

void Ethernet::setSourceMac(const uint8_t* address)
{
    memcpy(data() + SMAC_OFFSET, address, SMAC_SIZE);
}

void Ethernet::setDestinationMac(const uint8_t* address)
{
    memcpy(data() + DMAC_OFFSET, address, DMAC_SIZE);
}

const uint8_t* Ethernet::sourceMac() const
{
    return data() + SMAC_OFFSET;
}

const uint8_t* Ethernet::destinationMac() const
{
    return data() + DMAC_OFFSET;
}

}