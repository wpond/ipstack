#ifndef BASESTATION_NETWORKREADER_H
#define BASESTATION_NETWORKREADER_H

#include "basestation_packet.h"

#include <atomic>
#include <memory>
#include <functional>

namespace basestation
{

class NetworkReader
{
public:
    NetworkReader(
        int fd,
        std::function<void(std::shared_ptr<Packet>)> callback,
        const std::atomic_bool& stopFlag);

    void operator()();
private:
    int mFd;
    std::function<void(std::shared_ptr<Packet>)> mCallback;
    const std::atomic_bool& mStopFlag;
};

}

#endif