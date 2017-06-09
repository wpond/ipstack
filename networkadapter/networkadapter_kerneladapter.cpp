#include "networkadapter_kerneladapter.h"

#include <sstream>
#include <stdexcept>
#include <cstring>
#include <thread>

#include <sys/ioctl.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include <fcntl.h>
#include <unistd.h>
#include <stropts.h>

#include <linux/if.h>
#include <linux/if_tun.h>
#include <linux/ioctl.h>

namespace networkadapter
{

namespace
{

const std::string CLONE_DEV = "/dev/net/tun";
const std::string IP = "192.168.43.1";
const std::string MASK = "255.255.255.0";

}

KernelAdapter::KernelAdapter()
    : mStopFlag(false), mReadThread(0), mWriteThread(0)
{
    // Open interface
    struct ifreq ifr;
    int rc;

    mFd = open(CLONE_DEV.c_str(), O_RDWR);
    if (mFd < 0)
    {
        std::ostringstream oss;
        oss << "Failed to open network interface, "
            << "interface = [" << CLONE_DEV << "], "
            << "fd = " << mFd;
        throw std::runtime_error(oss.str());
    }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;

    rc = ioctl(mFd, TUNSETIFF, static_cast<void*>(&ifr));
    if (rc < 0)
    {
        close(mFd);
        std::ostringstream oss;
        oss << "Failed to create device, "
            << "rc = " << rc;
        throw std::runtime_error(oss.str());
    }

    mInterface = ifr.ifr_name;

    // Setup IP
    mSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (mSocket < 0)
    {
        close(mFd);
        std::ostringstream oss;
        oss << "Failed to open socket, "
            << "socket = " << mSocket;
        throw std::runtime_error(oss.str());
    }

    {
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_addr.s_addr = inet_addr(IP.c_str());
        addr.sin_family = AF_INET;
        memcpy(&ifr.ifr_addr, &addr, sizeof(struct sockaddr));
        rc = ioctl(mSocket, SIOCSIFADDR, &ifr);
        if (rc < 0)
        {
            close(mSocket);
            close(mFd);
            std::ostringstream oss;
            oss << "Failed to set IP address, "
                << "rc = " << rc << ", "
                << "errno = " << strerror(errno);
            throw std::runtime_error(oss.str());
        }
    }

    {
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_addr.s_addr = inet_addr(MASK.c_str());
        addr.sin_family = AF_INET;
        memcpy(&ifr.ifr_addr, &addr, sizeof(struct sockaddr));
        rc = ioctl(mSocket, SIOCSIFNETMASK, &ifr);
        if (rc < 0)
        {
            close(mSocket);
            close(mFd);
            std::ostringstream oss;
            oss << "Failed to set MASK address, "
                << "rc = " << rc << ", "
                << "errno = " << strerror(errno);
            throw std::runtime_error(oss.str());
        }
    }

    {
        rc = ioctl(mSocket, SIOCGIFHWADDR, &ifr);
        if (rc < 0)
        {
            close(mSocket);
            close(mFd);
            std::ostringstream oss;
            oss << "Faield to get hardware address, "
                << "rc = " << rc << ", "
                << "errno = " << strerror(errno);
            throw std::runtime_error(oss.str());
        }
        memcpy(mHardwareAddress, ifr.ifr_hwaddr.sa_data, sizeof(mHardwareAddress));
    }

    rc = ioctl(mSocket, SIOCGIFFLAGS, &ifr);
    if (rc < 0)
    {
        close(mSocket);
        close(mFd);
        std::ostringstream oss;
        oss << "Failed to read socket flags, "
            << "rc = " << rc;
        throw std::runtime_error(oss.str());
    }

    ifr.ifr_flags |= (IFF_UP | IFF_RUNNING);
    rc = ioctl(mSocket, SIOCSIFFLAGS, &ifr);
    if (rc < 0)
    {
        close(mSocket);
        close(mFd);
        std::ostringstream oss;
        oss << "Failed to set socket flags, "
            << "rc = " << rc;
        throw std::runtime_error(oss.str());
    }

    // Setup threads
    std::function<void(std::shared_ptr<networkutils::Packet>)> callback =
        std::bind(&KernelAdapter::notify, this, std::placeholders::_1);
    mReadThread = new std::thread(Reader(mFd, callback, mStopFlag));
    //mWriteThread = new std::thread(NetworkWriter(mFd, &mWriteQueue, &mStopFlag));
}

KernelAdapter::~KernelAdapter()
{
    mStopFlag = true;

    mReadThread->join();
    delete mReadThread;

    mWriteThread->join();
    delete mWriteThread;

    close(mSocket);
    close(mFd);
}

const std::string& KernelAdapter::interface() const
{
    return mInterface;
}

const uint8_t* KernelAdapter::hardwareAddress() const
{
    return mHardwareAddress;
}

void KernelAdapter::attach(Observer* observer)
{
    if (!observer)
    {
        throw std::runtime_error("Cannot attach NULL observer");
    }

    mObservers.insert(observer);
}

void KernelAdapter::detatch(Observer* observer)
{
    if (!observer)
    {
        throw std::runtime_error("Cannot detatch NULL observer");
    }

    mObservers.erase(observer);
}

void KernelAdapter::notify(std::shared_ptr<networkutils::Packet> packet)
{
    // TODO: could this be more efficient? do we have to join on the threads
    std::vector<std::thread> threads;
    for (auto observer : mObservers)
    {
        std::function<void()> func = std::bind(&Observer::receive, &(*observer), this, packet);
        threads.emplace_back(std::thread(func));
    }
    for (auto & thread : threads)
    {
        thread.join();
    }
}

void KernelAdapter::send(const std::shared_ptr<networkutils::Packet>& packet)
{
    const int bytes = write(mFd, packet->data(), packet->size());
    if ((uint32_t)bytes != packet->size())
    {
        std::ostringstream oss;
        oss << "Packet write resulted in unexpected number of bytes, "
            << "packet size = " << packet->size() << ", "
            << "bytes written = " << bytes;
        throw std::runtime_error(oss.str());
    }
}

}