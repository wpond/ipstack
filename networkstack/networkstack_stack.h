#ifndef NETWORKSTACK_STACK_H
#define NETWORKSTACK_STACK_H

#include <networkadapter_adapter.h>

#include <networkutils_macaddress.h>
#include <networkutils_ipaddress.h>

#include <networkpackets_ethernet.h>

#include <string>
#include <cstdint>

#include "networkstack_arptable.h"

namespace networkstack
{

class Stack : public networkadapter::Observer
{
public:
    Stack(
        networkadapter::Adapter* adapter,
        const std::string& ipAddress,
        const networkutils::MacAddress& hardwareAddress);
    virtual ~Stack();

    virtual void receive(
        networkadapter::Adapter* adapter,
        std::shared_ptr<networkutils::Packet> packet);
private:
    networkadapter::Adapter* mAdapter;
    const networkutils::IpAddress mIpAddress;
    networkutils::MacAddress mHardwareAddress;
    ArpTable mArpTable;

    void processArp(
        networkadapter::Adapter* adapter,
        const networkpackets::Ethernet& packet);
};

}

#endif