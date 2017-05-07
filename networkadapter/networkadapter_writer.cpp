#include "networkadapter_writer.h"

#include <stdexcept>
#include <sstream>

#include <unistd.h>

namespace networkadapter
{

Writer::Writer(
    int fd,
    std::queue<std::shared_ptr<networkutils::Packet> >* queue,
    const std::atomic_bool* stopFlag)
    : mStopFlag(stopFlag), mFd(fd), mQueue(queue)
{
    if (!mQueue)
    {
        throw std::runtime_error("Cannot create network writer, queue is NULL");
    }

    if (!mStopFlag)
    {
        throw std::runtime_error("Cannot create network writer, stopFlag is NULL");
    }
}

void Writer::operator()()
{
    while (!*mStopFlag)
    {
        if (mQueue->size() == 0)
        {
            continue;
        }

        std::shared_ptr<networkutils::Packet> packet = mQueue->front();

        const int bytes = write(mFd, packet->data(), packet->size());
        if ((uint32_t)bytes != packet->size())
        {
            std::ostringstream oss;
            oss << "Failed to send entire packet, "
                << "size = " << packet->size() << ", "
                << "bytes sent = " << bytes;
            throw std::runtime_error(oss.str());
        }

        mQueue->pop();
    }
}

}