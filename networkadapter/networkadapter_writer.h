#ifndef NETWORKADAPTER_WRITER_H
#define NETWORKADAPTER_WRITER_H

#include "networkstack_packet.h"

#include <queue>
#include <memory>
#include <atomic>

namespace networkadapter
{

class Writer
{
public:
    Writer(
        int fd,
        std::queue<std::shared_ptr<networkstack::Packet> >* queue,
        const std::atomic_bool* stopFlag);

    void operator()();
private:
    const std::atomic_bool* mStopFlag;
    int mFd;
    std::queue<std::shared_ptr<networkstack::Packet> >* mQueue;
};

}

#endif