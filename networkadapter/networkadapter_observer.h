#ifndef NETWORKADAPTER_OBSERVER_H
#define NETWORKADAPTER_OBSERVER_H

#include "networkstack_packet.h"

#include <memory>

namespace networkadapter
{

class Adapter;

class Observer
{
public:
    Observer() {}
    virtual ~Observer() {}

    // Pure virtual function
    virtual void receive(Adapter* adapter, std::shared_ptr<const networkstack::Packet> packet) = 0;
};

}

#endif