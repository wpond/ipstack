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
    static Arp fromPayload(std::shared_ptr<networkutils::Packet> payload);
    static Arp fromFullPacket(std::shared_ptr<networkutils::Packet> packet);

private:
    Arp(std::shared_ptr<networkutils::Packet> packet);
};

}

#endif