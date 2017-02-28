#include "basestation_packet.h"

#include <cstring>
#include <stdexcept>

namespace basestation
{

Packet::Packet(const char* data, int size)
    : mSize(size)
{
    mData = new char[size];
    memcpy(mData, data, size);
}

Packet::Packet(std::shared_ptr<Packet> packet, int start, int size)
    : mParent(packet)
{
    if (!packet)
    {
        throw std::runtime_error("Cannot create packet, passed NULL parent packet");
    }

    if (packet->size() > (size + start))
    {
        throw std::runtime_error("Cannot create packet, passed too small parent packet");
    }

    mData = packet->mData + start;
    mSize = (size) ? size : packet->mSize - start;
}

Packet::~Packet()
{
    delete[] mData;
}

const char* Packet::data() const
{
    return mData;
}

int Packet::size() const
{
    return mSize;
}

}