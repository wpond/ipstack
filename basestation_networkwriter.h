#ifndef BASESTATION_NETWORKWRITER_H
#define BASESTATION_NETWORKWRITER_H

#include "basestation_packet.h"

#include <queue>
#include <memory>
#include <atomic>

namespace basestation
{

class NetworkWriter
{
public:
    NetworkWriter(
        int fd,
        std::queue<std::shared_ptr<Packet> >* queue,
        const std::atomic_bool* stopFlag);

    void operator()();
private:
    const std::atomic_bool* mStopFlag;
    int mFd;
    std::queue<std::shared_ptr<Packet> >* mQueue;
};

}

#endif