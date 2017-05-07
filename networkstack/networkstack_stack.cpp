#include "networkstack_stack.h"

#include <stdexcept>

namespace networkstack
{

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
    std::shared_ptr<const networkutils::Packet> packet)
{
    if (adapter != mAdapter)
    {
        return;
    }

    
}

}