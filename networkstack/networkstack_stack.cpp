#include "networkstack_stack.h"

#include <stdexcept>
#include <cstring>

#include <networkpackets_ethernet.h>

namespace networkstack
{

namespace
{

const int ADDRESS_SIZE = 6;

}

Stack::Stack(
    networkadapter::Adapter* adapter,
    const std::string& ipAddress,
    const uint8_t* hardwareAddress)
    : mAdapter(adapter),
      mIpAddress(ipAddress),
      mHardwareAddress(hardwareAddress)
{
    if (!mAdapter)
    {
        throw std::runtime_error("Passed NULL adapter to stack");
    }
    
    mAdapter->attach(this);
}

Stack::~Stack()
{
    mAdapter->detatch(this);
}

void Stack::receive(
    networkadapter::Adapter* adapter,
    std::shared_ptr<networkutils::Packet> packet)
{
    if (adapter != mAdapter)
    {
        return;
    }

    networkpackets::Ethernet ethernet =
        networkpackets::Ethernet::fromFullPacket(packet);

    if (memcmp(mHardwareAddress, ethernet.destinationMac(), ADDRESS_SIZE))
    {
        return;
    }
    
}

}
