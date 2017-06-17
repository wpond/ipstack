#ifndef NETWORKPACKETS_ARP_H
#define NETWORKPACKETS_ARP_H

#include "networkpackets_genericinterface.h"

#include <memory>

#include <networkutils_packet.h>

namespace networkpackets
{

class Arp : public GenericInterface
{
public:
    static Arp emptyPacket();
    static Arp fromFullPacket(std::shared_ptr<networkutils::Packet> packet);

    Arp clone() const;

private:
    Arp(std::shared_ptr<networkutils::Packet> packet);
};

}

#endif