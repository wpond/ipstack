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

unsigned short ArpDecoder::hardwareType() const
{
    return mHardwareType;
}

unsigned short ArpDecoder::protocolType() const
{
    return mProtocolType;
}

unsigned char ArpDecoder::hardwareSize() const
{
    return mHardwareSize;
}

unsigned char ArpDecoder::protocolSize() const
{
    return mProtocolSize;
}

unsigned short ArpDecoder::opCode() const
{
    return mOpCode;
}

const std::shared_ptr<networkutils::Packet> ArpDecoder::payload() const
{
    return std::shared_ptr<networkutils::Packet>(new networkutils::Packet(mPacket, 8));
}

}