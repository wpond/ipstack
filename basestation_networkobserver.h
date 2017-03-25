#ifndef BASESTATION_NETWORKOBSERVER_H
#define BASESTATION_NETWORKOBSERVER_H

#include "basestation_packet.h"

#include <memory>

namespace basestation
{

class NetworkAdapter;

class NetworkObserver
{
public:
    NetworkObserver() {}
    virtual ~NetworkObserver() {}

    // Pure virtual function
    virtual void receive(NetworkAdapter* network, std::shared_ptr<const Packet> packet) = 0;
};

}

#endif