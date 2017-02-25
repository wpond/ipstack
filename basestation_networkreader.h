#ifndef BASESTATION_NETWORKREADER_H
#define BASESTATION_NETWORKREADER_H

#include "basestation_packet.h"

#include <queue>
#include <memory>
#include <atomic>

namespace basestation
{

class NetworkReader
{
public:
    NetworkReader(
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