#include <gtest/gtest.h>

#include <networkstack_stack.h>

#include "tests_testadapter.h"

class Stack : public ::testing::Test
{
public:
    void SetUp()
    {
        mAdapter = new tests::TestAdapter("192.168.0.1", mAdapterAddress);
        mStack = new networkstack::Stack(mAdapter, "192.68.0.2", mStackAddress);
        ASSERT_TRUE(mAdapter->testIsObserver(mStack));
    }

    void TearDown()
    {
        delete mStack;
        ASSERT_FALSE(mAdapter->testIsObserver(mStack));
        delete mAdapter;
    }
protected:
    const char mAdapterAddress[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
    tests::TestAdapter* mAdapter;

    const char mStackAddress[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 };
    networkstack::Stack* mStack;
};

TEST_F(Stack, ARPPacket)
{

}
