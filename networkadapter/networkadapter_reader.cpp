#include "networkadapter_reader.h"

#include <stdexcept>
#include <sstream>

#include <errno.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/select.h>

namespace networkadapter
{

namespace
{

const int MTU = 1500;
const int TIMEOUT = 1;  // seconds

}

Reader::Reader(
    int fd,
    std::function<void(std::shared_ptr<const networkstack::Packet>)> callback,
    const std::atomic_bool& stopFlag)
    : mFd(fd), mCallback(callback), mStopFlag(stopFlag)
{
    // Nothing to do
}

void Reader::operator()()
{
    char buffer[MTU];
    while (!mStopFlag)
    {
        struct timeval timeout;
        timeout.tv_usec = 0;
        timeout.tv_sec = TIMEOUT;

        fd_set set;
        FD_ZERO(&set);
        FD_SET(mFd, &set);

        const int rc = select(mFd + 1, &set, NULL, NULL, &timeout);
        if (rc == 0)
        {
            // Timeout
            continue;
        }
        if (rc < 0)
        {
            const int error = errno;
            if (error == EINTR)
            {
                // Interrupt
                continue;
            }

            // Error
            std::ostringstream oss;
            oss << "Reader select failed, "
                << "errno = " << error;
            throw std::runtime_error(oss.str());
        }

        int bytes = read(mFd, buffer, sizeof(buffer));
        if (bytes < 0)
        {
            // failed to read from device
            throw std::runtime_error("Failed to read from network");
        }

        std::shared_ptr<const networkstack::Packet> packet(new networkstack::Packet(buffer, bytes));
        mCallback(packet);
    }
}

}