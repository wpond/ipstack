#ifndef NETWORKADAPTER_ADAPTER_H
#define NETWORKADAPTER_ADAPTER_H

#include <string>
#include <queue>
#include <memory>
#include <thread>
#include <set>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "networkstack_packet.h"
#include "networkadapter_reader.h"
#include "networkadapter_writer.h"
#include "networkadapter_observer.h"

namespace networkadapter
{

class Adapter
{
public:
    Adapter();
    ~Adapter();

    const std::string& interface() const;

    void attach(Observer* observer);
    void detatch(Observer* observer);

    // Send a packet
    void send(const std::shared_ptr<networkstack::Packet>& packet);

private:
    std::string mInterface;
    int mFd;
    int mSocket;

    // Notify observers of packet
    void notify(std::shared_ptr<const networkstack::Packet> packet);

    std::set<Observer*> mObservers;

    std::queue<std::shared_ptr<networkstack::Packet> > mSendQueue;
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