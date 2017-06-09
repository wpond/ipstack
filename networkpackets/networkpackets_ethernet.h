#ifndef NETWORKPACKETS_ETHERNET_H
#define NETWORKPACKETS_ETHERNET_H

#include "networkpackets_genericinterface.h"

#include <memory>

#include <networkutils_packet.h>

namespace networkpackets
{

class Ethernet : public GenericInterface
{
public:
    static Ethernet fromPayload(std::shared_ptr<networkutils::Packet> payload);
    static Ethernet fromFullPacket(std::shared_ptr<networkutils::Packet> packet);

    void setSourceMac(const uint8_t* address);
    void setDestinationMac(const uint8_t* address);
    const uint8_t* sourceMac() const;
    const uint8_t* destinationMac() const;

private:
    Ethernet(std::shared_ptr<networkutils::Packet> packet);

};

}

#endif