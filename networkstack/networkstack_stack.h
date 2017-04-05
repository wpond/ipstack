#ifndef NETWORKSTACK_STACK_H
#define NETWORKSTACK_STACK_H

#include <networkadapter_adapter.h>

#include <string>

namespace networkstack
{

class Stack : public networkadapter::Observer
{
public:
    Stack(
        networkadapter::Adapter* adapter,
        const std::string& ipAddress,
        const char* hardwareAddress);
    virtual ~Stack();

    virtual void receive(
        networkadapter::Adapter* adapter,
        std::shared_ptr<const networkutils::Packet> packet);
private:
    networkadapter::Adapter* mAdapter;
    const std::string mIpAddress;
    const char* mHardwareAddress;
};

}

#endif