#ifndef NETWORKPACKETS_ARPFACTORY_H
#define NETWORKPACKETS_ARPFACTORY_H

#include <networkutils_packet.h>

#include <memory>

namespace networkpackets
{

class ArpFactory
{
public:
    ArpFactory(unsigned short opcode, const char* payload, int size);

    void setHardwareType(unsigned short hardwareType);
    void setProtocolType(unsigned short protocolType);
    void setHardwareSize(unsigned char hardwareSize);
    void setProtocolSize(unsigned char protocolSize);

    std::shared_ptr<networkutils::Packet> getPacket() const;

private:
    unsigned short mHardwareType;
    unsigned short mProtocolType;
    unsigned char mHardwareSize;
    unsigned char mProtocolSize;
    unsigned short mOpCode;
    const char* mPayload;
    int mSize;

    int totalSize() const;
    int writeHardwareType(char* destination) const;
    int writeProtocolType(char* destination) const;
    int writeHardwareSize(char* destination) const;
    int writeProtocolSize(char* destination) const;
    int writeOpCode(char* destination) const;
    void writePayload(char* destination) const;

    int writeNetworkShort(char* destination, unsigned short value) const;
};

}

#endif