#include "basestation_network.h"

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

namespace basestation
{

namespace
{

const std::string CLONE_DEV = "/dev/net/tun";
const std::string IP = "192.168.43.1";
const std::string MASK = "255.255.255.0";

}

Network::Network()
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
    std::function<void(std::shared_ptr<Packet>)> callback =
        std::bind(&Network::notify, this, std::placeholders::_1);
    mReadThread = new std::thread(NetworkReader(mFd, callback, mStopFlag));
    //mWriteThread = new std::thread(NetworkWriter(mFd, &mWriteQueue, &mStopFlag));
}

Network::~Network()
{
    mStopFlag = true;

    mReadThread->join();
    delete mReadThread;

    mWriteThread->join();
    delete mWriteThread;

    close(mSocket);
    close(mFd);
}

const std::string& Network::interface() const
{
    return mInterface;
}

void Network::attach(NetworkObserver* observer)
{
    if (!observer)
    {
        throw std::runtime_error("Cannot attach NULL observer");
    }

    mObservers.insert(observer);
}

void Network::detatch(NetworkObserver* observer)
{
    if (!observer)
    {
        throw std::runtime_error("Cannot detatch NULL observer");
    }

    mObservers.erase(observer);
}

void Network::notify(std::shared_ptr<Packet> packet)
{
    // TODO: could this be more efficient? do we have to join on the threads
    std::vector<std::thread> threads;
    for (auto observer : mObservers)
    {
        std::function<void()> func = std::bind(&NetworkObserver::receive, &(*observer), packet);
        threads.emplace_back(std::thread(func));
    }
    for (auto & thread : threads)
    {
        thread.join();
    }
}

}