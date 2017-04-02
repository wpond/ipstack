#include "networkstack_stack.h"

#include <stdexcept>

namespace networkstack
{

Stack::Stack(
    networkadapter::Adapter* adapter,
    const std::string& ipAddress,
    const char* hardwareAddress)
    : mAdapter(adapter),
      mIpAddress(ipAddress),
      mHardwareAddress(hardwareAddress)
{
    if (!mAdapter)
    {
        throw std::runtime_error("Passed NULL adapter to stack");
    }
    
    // attach to adapter
}

Stack::~Stack()
{
    // detatch observer
}

}