#ifndef NETWORKADAPTER_READER_H
#define NETWORKADAPTER_READER_H

#include <networkutils_packet.h>

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
        std::function<void(std::shared_ptr<networkutils::Packet>)> callback,
        const std::atomic_bool& stopFlag);

    void operator()();
private:
    int mFd;
    std::function<void(std::shared_ptr<networkutils::Packet>)> mCallback;
    const std::atomic_bool& mStopFlag;
};

}

#endif