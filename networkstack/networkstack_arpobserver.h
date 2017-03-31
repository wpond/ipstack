#ifndef NETWORKSTACK_ARPOBSERVER_H
#define NETWORKSTACK_ARPOBSERVER_H

#include "networkstack_packet.h"
#include "networkadapter_adapter.h"
#include "networkadapter_observer.h"

#include <memory>

namespace networkstack
{

class ArpObserver : public networkadapter::Observer
{
public:
    void receive(
        networkadapter::Adapter* network,
        std::shared_ptr<const Packet> packet);
private:

};

}

#endif