#ifndef NETWORKADAPTER_ADAPTER
#define NETWORKADAPTER_ADAPTER

#include <networkutils_packet.h>

#include <cstdint>

#include "networkadapter_observer.h"

namespace networkadapter
{

class Adapter
{
public:
    Adapter() {}
    virtual ~Adapter() {};

    virtual const std::string& interface() const = 0;
    virtual const uint8_t* hardwareAddress() const = 0;

    virtual void attach(Observer* observer) = 0;
    virtual void detatch(Observer* observer) = 0;

    // Send a packet
    virtual void send(const std::shared_ptr<networkutils::Packet>& packet) = 0;
};

}

#endif