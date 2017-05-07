#include <gtest/gtest.h>

#include <cstdint>

#include <networkstack_stack.h>

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
    const uint8_t mAdapterAddress[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
    tests::TestAdapter* mAdapter;

    const char mStackIp[13] = "192.168.0.2";
    const uint8_t mStackAddress[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 };
    networkstack::Stack* mStack;
};

TEST_F(Stack, ARPPacket)
{
    
}
