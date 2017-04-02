#include "tests_adapter.h"

namespace tests
{

Adapter::Adapter(const std::string& interface, const char* hardwareAddress)
    : mInterface(interface), mHardwareAddress(hardwareAddress)
{

}

Adapter::~Adapter()
{

}

const std::string& Adapter::interface() const
{
    return mInterface;
}

const char* Adapter::hardwareAddress() const
{
    return mHardwareAddress;
}

void Adapter::attach(networkadapter::Observer* observer)
{
    if (!observer)
    {
        throw std::runtime_error("Cannot attach NULL observer");
    }

    mObservers.insert(observer);
}

void Adapter::detatch(networkadapter::Observer* observer)
{
    if (!observer)
    {
        throw std::runtime_error("Cannot detatch NULL observer");
    }

    mObservers.erase(observer);
}

void Adapter::send(const std::shared_ptr<networkutils::Packet>& packet)
{
    mSentQueue.push(packet);
}

void Adapter::testReceive(std::shared_ptr<const networkutils::Packet> packet)
{
    for (networkadapter::Observer* observer : mObservers)
    {
        observer->receive(this, packet);
    }
}

std::shared_ptr<networkutils::Packet> Adapter::testSent()
{
    std::shared_ptr<networkutils::Packet> packet;
    if (!mSentQueue.empty())
    {
        packet = mSentQueue.front();
        mSentQueue.pop();
    }

    return packet;
}

}