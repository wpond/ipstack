#ifndef NETWORKSTACK_STACK_H
#define NETWORKSTACK_STACK_H

#include <networkadapter_adapter.h>

#include <string>

#include "networkstack_observer.h"

namespace networkstack
{

class Stack
{
public:
    Stack(
        networkadapter::Adapter* adapter,
        const std::string& ipAddress,
        const char* hardwareAddress);
    ~Stack();
private:
    networkadapter::Adapter* mAdapter;
    const std::string mIpAddress;
    const char* mHardwareAddress;
};

}

#endif