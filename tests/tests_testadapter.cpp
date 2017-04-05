#include "tests_testadapter.h"

namespace tests
{

TestAdapter::TestAdapter(const std::string& interface, const char* hardwareAddress)
    : mInterface(interface), mHardwareAddress(hardwareAddress)
{

}

TestAdapter::~TestAdapter()
{

}

const std::string& TestAdapter::interface() const
{
    return mInterface;
}

const char* TestAdapter::hardwareAddress() const
{
    return mHardwareAddress;
}

void TestAdapter::attach(networkadapter::Observer* observer)
{
    if (!observer)
    {
        throw std::runtime_error("Cannot attach NULL observer");
    }

    mObservers.insert(observer);
}

void TestAdapter::detatch(networkadapter::Observer* observer)
{
    if (!observer)
    {
        throw std::runtime_error("Cannot detatch NULL observer");
    }

    mObservers.erase(observer);
}

void TestAdapter::send(const std::shared_ptr<networkutils::Packet>& packet)
{
    mSentQueue.push(packet);
}

void TestAdapter::testReceive(std::shared_ptr<const networkutils::Packet> packet)
{
    for (networkadapter::Observer* observer : mObservers)
    {
        observer->receive(this, packet);
    }
}

std::shared_ptr<networkutils::Packet> TestAdapter::testSent()
{
    std::shared_ptr<networkutils::Packet> packet;
    if (!mSentQueue.empty())
    {
        packet = mSentQueue.front();
        mSentQueue.pop();
    }

    return packet;
}

const std::set<networkadapter::Observer*> TestAdapter::testObservers() const
{
    return mObservers;
}

bool TestAdapter::testIsObserver(networkadapter::Observer* observer) const
{
    return mObservers.find(observer) != mObservers.end();
}

}