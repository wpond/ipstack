#ifndef NETWORKPACKETS_ARPFACTORY_H
#define NETWORKPACKETS_ARPFACTORY_H

#include <networkutils_packet.h>

#include <memory>
#include <cstdint>

namespace networkpackets
{

class ArpFactory
{
public:
    ArpFactory(uint16_t opcode, const uint8_t* payload, uint32_t size);

    void setHardwareType(uint16_t hardwareType);
    void setProtocolType(uint16_t protocolType);
    void setHardwareSize(uint8_t hardwareSize);
    void setProtocolSize(uint8_t protocolSize);

    std::shared_ptr<networkutils::Packet> getPacket() const;

private:
    uint16_t mHardwareType;
    uint16_t mProtocolType;
    uint8_t mHardwareSize;
    uint8_t mProtocolSize;
    uint16_t mOpCode;
    const uint8_t* mPayload;
    uint32_t mSize;

    uint32_t totalSize() const;
    uint32_t writeHardwareType(uint8_t* destination) const;
    uint32_t writeProtocolType(uint8_t* destination) const;
    uint32_t writeHardwareSize(uint8_t* destination) const;
    uint32_t writeProtocolSize(uint8_t* destination) const;
    uint32_t writeOpCode(uint8_t* destination) const;
    void writePayload(uint8_t* destination) const;

    uint32_t writeNetworkShort(uint8_t* destination, uint16_t value) const;
};

}

#endif