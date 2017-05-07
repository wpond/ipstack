#ifndef NETWORKPACKETS_ARPDECODER_H
#define NETWORKPACKETS_ARPDECODER_H

#include <networkutils_packet.h>

#include <memory>
#include <cstdint>

namespace networkpackets
{

class ArpDecoder
{
public:
    ArpDecoder(const std::shared_ptr<networkutils::Packet> packet);

    uint16_t hardwareType() const;
    uint16_t protocolType() const;
    uint8_t hardwareSize() const;
    uint8_t protocolSize() const;
    uint16_t opCode() const;
    const std::shared_ptr<networkutils::Packet> payload() const;
private:
    uint16_t mHardwareType;
    uint16_t mProtocolType;
    uint8_t mHardwareSize;
    uint8_t mProtocolSize;
    uint16_t mOpCode;
    const std::shared_ptr<networkutils::Packet> mPacket;
};

}

#endif