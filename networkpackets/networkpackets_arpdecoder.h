#ifndef NETWORKPACKETS_ARPDECODER_H
#define NETWORKPACKETS_ARPDECODER_H

#include <networkutils_packet.h>

#include <memory>

namespace networkpackets
{

class ArpDecoder
{
public:
    ArpDecoder(const std::shared_ptr<networkutils::Packet> packet);

    unsigned short hardwareType() const;
    unsigned short protocolType() const;
    unsigned char hardwareSize() const;
    unsigned char protocolSize() const;
    unsigned short opCode() const;
    const std::shared_ptr<networkutils::Packet> payload() const;
private:
    unsigned short mHardwareType;
    unsigned short mProtocolType;
    unsigned char mHardwareSize;
    unsigned char mProtocolSize;
    unsigned short mOpCode;
    const std::shared_ptr<networkutils::Packet> mPacket;
};

}

#endif