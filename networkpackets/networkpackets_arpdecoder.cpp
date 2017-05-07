#include "networkpackets_arpdecoder.h"

#include <arpa/inet.h>

#include <stdexcept>

namespace networkpackets
{

ArpDecoder::ArpDecoder(const std::shared_ptr<networkutils::Packet> packet)
    : mPacket(packet)
{
    if (!mPacket)
    {
        throw std::runtime_error("ARP decoder passed NULL packet");
    }

    mHardwareType = ntohs(*(mPacket->data()));
    mProtocolType = ntohs(*(mPacket->data() + 2));
    mHardwareSize = *(mPacket->data() + 4);
    mProtocolSize = *(mPacket->data() + 5);
    mOpCode = ntohs(*(mPacket->data() + 6));
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