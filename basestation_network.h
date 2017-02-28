#ifndef BASESTATION_NETWORK_H
#define BASESTATION_NETWORK_H

#include <string>
#include <queue>
#include <memory>
#include <thread>
#include <set>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "basestation_packet.h"
#include "basestation_networkreader.h"
#include "basestation_networkwriter.h"
#include "basestation_networkobserver.h"

namespace basestation
{

class Network
{
public:
    Network();
    ~Network();

    const std::string& interface() const;

    void attach(NetworkObserver* observer);
    void detatch(NetworkObserver* observer);

    // Send a packet
    void send(const std::shared_ptr<Packet>& packet);

private:
    std::string mInterface;
    int mFd;
    int mSocket;

    // Notify observers of packet
    void notify(std::shared_ptr<Packet> packet);

    std::set<NetworkObserver*> mObservers;

    std::queue<std::shared_ptr<Packet> > mSendQueue;
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