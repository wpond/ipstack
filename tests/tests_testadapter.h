#ifndef TESTS_ADAPTER_H
#define TESTS_ADAPTER_H

#include <networkadapter_adapter.h>
#include <networkadapter_observer.h>

#include <networkutils_packet.h>
#include <networkutils_macaddress.h>

#include <memory>
#include <string>
#include <set>
#include <queue>

namespace tests
{

class TestAdapter : public networkadapter::Adapter
{
public:
    TestAdapter(const std::string& interface, const networkutils::MacAddress& hardwareAddress);
    virtual ~TestAdapter();

    virtual const std::string& interface() const;
    virtual const networkutils::MacAddress& hardwareAddress() const;

    virtual void attach(networkadapter::Observer* observer);
    virtual void detatch(networkadapter::Observer* observer);

    virtual void send(const std::shared_ptr<networkutils::Packet>& packet);

    // Test interface
    void testReceive(std::shared_ptr<networkutils::Packet> packet);
    std::shared_ptr<networkutils::Packet> testSent();
    const std::set<networkadapter::Observer*> testObservers() const;
    bool testIsObserver(networkadapter::Observer* observer) const;

private:
    std::set<networkadapter::Observer*> mObservers;
    std::queue<std::shared_ptr<networkutils::Packet> > mSentQueue;
    std::string mInterface;
    networkutils::MacAddress mHardwareAddress;
};

}

#endif