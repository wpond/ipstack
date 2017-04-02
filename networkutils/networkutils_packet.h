#ifndef NETWORKUTILS_PACKET_H
#define NETWORKUTILS_PACKET_H

#include <memory>

namespace networkutils
{

class Packet
{
public:
    Packet(const char* data, int size);
    Packet(std::shared_ptr<Packet> packet, int start=0, int size=0);
    ~Packet();

    const char* data() const;
    int size() const;
private:
    Packet(const Packet& that);

    char* mData;
    int mSize;
    std::shared_ptr<Packet> mParent;
};

}

#endif