#ifndef TESTS_TESTADAPTER_H
#define TESTS_TESTADAPTER_H

#include <networkadapter_adapter.h>
#include <networkadapter_observer.h>

#include <networkutils_packet.h>

#include <memory>
#include <string>
#include <set>
#include <queue>

namespace tests
{

class TestAdapter : public networkadapter::Adapter
{
public:
    TestAdapter(const std::string& interface, const char* hardwareAddress);
    virtual ~TestAdapter();

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

}

#endif