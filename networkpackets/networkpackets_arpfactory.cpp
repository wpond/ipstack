#include "networkpackets_arpfactory.h"

#include <arpa/inet.h>

#include <cstring>

namespace networkpackets
{

ArpFactory::ArpFactory(unsigned short opCode, const char* payload, int size)
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
    int size = totalSize();
    char data[size];
    int position = 0;

    position += writeHardwareType(data + position);
    position += writeProtocolType(data + position);
    position += writeHardwareSize(data + position);
    position += writeProtocolSize(data + position);
    position += writeOpCode(data + position);
    
    writePayload(data + position);

    return std::shared_ptr<networkutils::Packet>(new networkutils::Packet(data, size));
}

void ArpFactory::setHardwareType(unsigned short hardwareType)
{
    mHardwareType = hardwareType;
}

void ArpFactory::setProtocolType(unsigned short protocolType)
{
    mProtocolType = protocolType;
}

void ArpFactory::setHardwareSize(unsigned char hardwareSize)
{
    mHardwareSize = hardwareSize;
}

void ArpFactory::setProtocolSize(unsigned char protocolSize)
{
    mProtocolSize = protocolSize;
}

int ArpFactory::totalSize() const
{
    return
        sizeof(mHardwareType) +
        sizeof(mProtocolType) +
        sizeof(mHardwareSize) +
        sizeof(mProtocolSize) +
        sizeof(mOpCode) +
        mSize;
}

int ArpFactory::writeHardwareType(char* destination) const
{
    return writeNetworkShort(destination, mHardwareType);
}

int ArpFactory::writeProtocolType(char* destination) const
{
    return writeNetworkShort(destination, mProtocolType);
}

int ArpFactory::writeHardwareSize(char* destination) const
{
    *destination = mHardwareSize;
    return 1;
}

int ArpFactory::writeProtocolSize(char* destination) const
{
    *destination = mProtocolSize;
    return 1;
}

int ArpFactory::writeOpCode(char* destination) const
{
    return writeNetworkShort(destination, mOpCode);
}

void ArpFactory::writePayload(char* destination) const
{
    memcpy(destination, mPayload, mSize);
}

int ArpFactory::writeNetworkShort(char* destination, unsigned short value) const
{
    unsigned short networkShort = htons(value);
    memcpy(destination, &networkShort, sizeof(networkShort));
    return sizeof(networkShort);
}

}