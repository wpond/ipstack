#ifndef BASESTATION_NETWORK_H
#define BASESTATION_NETWORK_H

#include <string>
#include <queue>
#include <memory>
#include <thread>
#include <atomic>

#include "basestation_packet.h"
#include "basestation_networkreader.h"
#include "basestation_networkwriter.h"

namespace basestation
{

class Network
{
public:
    Network();
    ~Network();

    const std::string& interface() const;

    std::shared_ptr<Packet> read();
    void write(std::shared_ptr<Packet> packet);

private:
    std::string mInterface;
    int mFd;
    int mSocket;

    std::queue<std::shared_ptr<Packet> > mReadQueue;
    std::queue<std::shared_ptr<Packet> > mWriteQueue;

    std::atomic_bool mStopFlag;

    std::thread* mReadThread;
    std::thread* mWriteThread;
};

}

#endif