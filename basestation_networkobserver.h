#ifndef BASESTATION_NETWORKOBSERVER_H
#define BASESTATION_NETWORKOBSERVER_H

#include "basestation_packet.h"

#include <memory>

namespace basestation
{

class Network;

class NetworkObserver
{
public:
    NetworkObserver() {}
    virtual ~NetworkObserver() {}

    // Pure virtual function
    virtual void receive(Network* network, std::shared_ptr<Packet> packet) = 0;
};

}

#endif