#include "networkpackets_arpfactory.h"

#include <arpa/inet.h>

#include <cstring>

namespace networkpackets
{

ArpFactory::ArpFactory(uint16_t opCode, const uint8_t* payload, uint32_t size)
    : mHardwareType(0x0001),
      mProtocolType(0x0800),
      mHardwareSize(0x06),
      mProtocolSize(0x04),
      mOpCode(opCode),
      mPayload(payload),
      mSize(size)
{

}

std::shared_ptr<networkutils::Packet> ArpFactory::getPacket() const
{
    const uint32_t size = totalSize();
    uint8_t data[size];
    uint32_t position = 0;

    position += writeHardwareType(data + position);
    position += writeProtocolType(data + position);
    position += writeHardwareSize(data + position);
    position += writeProtocolSize(data + position);
    position += writeOpCode(data + position);
    
    writePayload(data + position);

    return std::shared_ptr<networkutils::Packet>(new networkutils::Packet(data, size));
}

void ArpFactory::setHardwareType(uint16_t hardwareType)
{
    mHardwareType = hardwareType;
}

void ArpFactory::setProtocolType(uint16_t protocolType)
{
    mProtocolType = protocolType;
}

void ArpFactory::setHardwareSize(uint8_t hardwareSize)
{
    mHardwareSize = hardwareSize;
}

void ArpFactory::setProtocolSize(uint8_t protocolSize)
{
    mProtocolSize = protocolSize;
}

uint32_t ArpFactory::totalSize() const
{
    return
        sizeof(mHardwareType) +
        sizeof(mProtocolType) +
        sizeof(mHardwareSize) +
        sizeof(mProtocolSize) +
        sizeof(mOpCode) +
        mSize;
}

uint32_t ArpFactory::writeHardwareType(uint8_t* destination) const
{
    return writeNetworkShort(destination, mHardwareType);
}

uint32_t ArpFactory::writeProtocolType(uint8_t* destination) const
{
    return writeNetworkShort(destination, mProtocolType);
}

uint32_t ArpFactory::writeHardwareSize(uint8_t* destination) const
{
    *destination = mHardwareSize;
    return 1;
}

uint32_t ArpFactory::writeProtocolSize(uint8_t* destination) const
{
    *destination = mProtocolSize;
    return 1;
}

uint32_t ArpFactory::writeOpCode(uint8_t* destination) const
{
    return writeNetworkShort(destination, mOpCode);
}

void ArpFactory::writePayload(uint8_t* destination) const
{
    memcpy(destination, mPayload, mSize);
}

uint32_t ArpFactory::writeNetworkShort(uint8_t* destination, uint16_t value) const
{
    uint16_t networkShort = htons(value);
    memcpy(destination, &networkShort, sizeof(networkShort));
    return sizeof(networkShort);
}

}