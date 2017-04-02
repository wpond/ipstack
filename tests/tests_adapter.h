#ifndef TESTS_ADAPTER_H
#define TESTS_ADAPTER_H

#include <networkadapter_adapter.h>
#include <networkadapter_observer.h>

#include <networkutils_packet.h>

#include <memory>
#include <string>
#include <set>
#include <queue>

namespace tests
{

class Adapter : public networkadapter::Adapter
{
public:
    Adapter(const std::string& interface, const char* hardwareAddress);
    virtual ~Adapter();

    virtual const std::string& interface() const;
    virtual const char* hardwareAddress() const;

    virtual void attach(networkadapter::Observer* observer);
    virtual void detatch(networkadapter::Observer* observer);

    virtual void send(const std::shared_ptr<networkutils::Packet>& packet);

    // Test receiving a packet
    void testReceive(std::shared_ptr<const networkutils::Packet> packet);
    std::shared_ptr<networkutils::Packet> testSent();

private:
    std::set<networkadapter::Observer*> mObservers;
    std::queue<std::shared_ptr<networkutils::Packet> > mSentQueue;
    std::string mInterface;
    const char* mHardwareAddress;
};

class Observer : public networkadapter::Observer
{
public:
    Observer() {}
    virtual ~Observer() {}
    virtual void receive(
        networkadapter::Adapter* adapter,
        std::shared_ptr<const networkutils::Packet> packet)
    {
        mQueue.push(packet);
    }

    std::shared_ptr<const networkutils::Packet> received()
    {
        std::shared_ptr<const networkutils::Packet> packet;
        if (!mQueue.empty())
        {
            packet = mQueue.front();
            mQueue.pop();
        }
        return packet;
    }

private:
    std::queue<std::shared_ptr<const networkutils::Packet> > mQueue;
};


}

#endif