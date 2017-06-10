#include "networkpackets_arpdecoder.h"

#include <arpa/inet.h>

#include <stdexcept>
#include <cstring>

namespace networkpackets
{

namespace
{

uint16_t extractUint16(uint8_t* base, uint16_t offset)
{
    uint16_t value = 0;
    memcpy(&value, base + offset, sizeof(value));
    return value;
}

}

ArpDecoder::ArpDecoder(const std::shared_ptr<networkutils::Packet> packet)
    : mPacket(packet)
{
    if (!mPacket)
    {
        throw std::runtime_error("ARP decoder passed NULL packet");
    }

    mHardwareType = ntohs(extractUint16(mPacket->data(), 0));
    mProtocolType = ntohs(extractUint16(mPacket->data(), 2));
    mHardwareSize = *(mPacket->data() + 4);
    mProtocolSize = *(mPacket->data() + 5);
    mOpCode = ntohs(extractUint16(mPacket->data(), 6));
}

uint16_t ArpDecoder::hardwareType() const
{
    return mHardwareType;
}

uint16_t ArpDecoder::protocolType() const
{
    return mProtocolType;
}

uint8_t ArpDecoder::hardwareSize() const
{
    return mHardwareSize;
}

uint8_t ArpDecoder::protocolSize() const
{
    return mProtocolSize;
}

uint16_t ArpDecoder::opCode() const
{
    return mOpCode;
}

const std::shared_ptr<networkutils::Packet> ArpDecoder::payload() const
{
    return std::shared_ptr<networkutils::Packet>(new networkutils::Packet(mPacket, 8));
}

}