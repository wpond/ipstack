#ifndef BASESTATION_PACKET_H
#define BASESTATION_PACKET_H

#include <memory>

namespace basestation
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
    char* mData;
    int mSize;
    std::shared_ptr<Packet> mParent;
};

}

#endif