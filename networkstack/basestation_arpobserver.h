#ifndef BASESTATION_ARPOBSERVER_H
#define BASESTATION_ARPOBSERVER_H

#include "basestation_packet.h"
#include "basestation_networkadapter.h"
#include "basestation_networkobserver.h"

#include <memory>

namespace basestation
{

class ArpObserver : public NetworkObserver
{
public:
    void receive(
        basestation::NetworkAdapter* network,
        std::shared_ptr<const basestation::Packet> packet);
private:

};

}

#endif