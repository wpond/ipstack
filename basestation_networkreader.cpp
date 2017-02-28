#include "basestation_networkreader.h"

#include <stdexcept>
#include <sstream>

#include <errno.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/select.h>

namespace basestation
{

namespace
{

const int MTU = 1500;
const int TIMEOUT = 1;  // seconds

}

NetworkReader::NetworkReader(
    int fd,
    std::function<void(std::shared_ptr<Packet>)> callback,
    const std::atomic_bool& stopFlag)
    : mFd(fd), mCallback(callback), mStopFlag(stopFlag)
{
    // Nothing to do
}

void NetworkReader::operator()()
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

        std::shared_ptr<Packet> packet(new Packet(buffer, bytes));
        mCallback(packet);
    }
}

}