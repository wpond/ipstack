#ifndef NETWORKADAPTER_KERNELADAPTER_H
#define NETWORKADAPTER_KERNELADAPTER_H

#include <string>
#include <queue>
#include <memory>
#include <thread>
#include <set>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <cstdint>

#include <networkutils_packet.h>

#include "networkadapter_adapter.h"
#include "networkadapter_reader.h"
#include "networkadapter_writer.h"
#include "networkadapter_observer.h"

namespace networkadapter
{

class KernelAdapter : public Adapter
{
public:
    KernelAdapter();
    virtual ~KernelAdapter();

    virtual const std::string& interface() const;
    virtual const uint8_t* hardwareAddress() const;

    virtual void attach(Observer* observer);
    virtual void detatch(Observer* observer);

    // Send a packet
    virtual void send(const std::shared_ptr<networkutils::Packet>& packet);

private:
    KernelAdapter(const KernelAdapter& that);

    std::string mInterface;
    uint8_t mHardwareAddress[6];
    int32_t mFd;
    int32_t mSocket;

    // Notify observers of packet
    void notify(std::shared_ptr<networkutils::Packet> packet);

    std::set<Observer*> mObservers;

    std::queue<std::shared_ptr<networkutils::Packet> > mSendQueue;
    std::mutex mSendLock;  // Lock this to access send queue
    std::condition_variable mSendCondition;  // Used to notify sender that there are packets

    std::atomic_bool mStopFlag;

    // calls notify on receive packet, blocks on select, calls receive() on obs in new thread?
    std::thread* mReadThread;
    // waits for a condition, writes all packets in it's queue
    std::thread* mWriteThread;
};

}

#endif