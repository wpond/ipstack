#include <gtest/gtest.h>

#include <cstdint>

#include <networkutils_macaddress.h>

#include <networkstack_stack.h>

#include <networkpackets_ethernet.h>

#include "tests_testadapter.h"

class Stack : public ::testing::Test
{
public:
    void SetUp()
    {
        mAdapter = new tests::TestAdapter(mAdapterIp, mAdapterAddress);
        ASSERT_EQ(0, mAdapter->testObservers().size());
        mStack = new networkstack::Stack(mAdapter, mStackIp, mStackAddress);
        ASSERT_EQ(1, mAdapter->testObservers().size());
        ASSERT_TRUE(mAdapter->testIsObserver(mStack));
    }

    void TearDown()
    {
        ASSERT_EQ(1, mAdapter->testObservers().size());
        ASSERT_TRUE(mAdapter->testIsObserver(mStack));
        delete mStack;
        ASSERT_FALSE(mAdapter->testIsObserver(mStack));
        ASSERT_EQ(0, mAdapter->testObservers().size());
        delete mAdapter;
    }
protected:
    const char mAdapterIp[13] = "192.168.0.1";
    const networkutils::MacAddress mAdapterAddress = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
    tests::TestAdapter* mAdapter;

    const char mStackIp[13] = "192.168.0.2";
    const networkutils::MacAddress mStackAddress = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 };
    networkstack::Stack* mStack;
};

TEST_F(Stack, NoOp)
{
    ASSERT_EQ(false, static_cast<bool>(mAdapter->testSent()));
}

TEST_F(Stack, WrongDestinationMac)
{
    std::shared_ptr<networkutils::Packet> emptyPayload(new networkutils::Packet(0, 0));

    networkpackets::Ethernet ethernet =
        networkpackets::Ethernet::fromPayload(emptyPayload);

    ethernet.setMacAddress("DestinationMac", { 0, 0, 0, 0, 0, 3 });
    ethernet.setMacAddress("SourceMac", { 0, 0, 0, 0, 0, 1 });

    {
        const uint16_t etherType = 0;
        ethernet.setUint16("EtherType", etherType);
    }

    mAdapter->testReceive(ethernet.getPacket());

    ASSERT_EQ(false, static_cast<bool>(mAdapter->testSent()));
}
