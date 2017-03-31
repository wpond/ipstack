#ifndef NETWORKADAPTER_READER_H
#define NETWORKADAPTER_READER_H

#include "networkstack_packet.h"

#include <atomic>
#include <memory>
#include <functional>

namespace networkadapter
{

class Reader
{
public:
    Reader(
        int fd,
        std::function<void(std::shared_ptr<const networkstack::Packet>)> callback,
        const std::atomic_bool& stopFlag);

    void operator()();
private:
    int mFd;
    std::function<void(std::shared_ptr<const networkstack::Packet>)> mCallback;
    const std::atomic_bool& mStopFlag;
};

}

#endif