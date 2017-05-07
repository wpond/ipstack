#include "networkutils_packet.h"

#include <cstring>
#include <stdexcept>

namespace networkutils
{

Packet::Packet(const uint8_t* data, uint32_t size)
    : mSize(size)
{
    mData = new uint8_t[size];
    memcpy(mData, data, size);
}

Packet::Packet(std::shared_ptr<Packet> packet, uint32_t start, uint32_t size)
    : mParent(packet)
{
    if (!packet)
    {
        throw std::runtime_error("Cannot create packet, passed NULL parent packet");
    }

    if (packet->size() < (size + start))
    {
        throw std::runtime_error("Cannot create packet, passed too small parent packet");
    }

    mData = packet->mData + start;
    mSize = (size) ? size : packet->mSize - start;
}

Packet::~Packet()
{
    if (!mParent)
    {
        delete[] mData;
    }
}

uint8_t* Packet::data()
{
    return mData;
}

const uint8_t* Packet::data() const
{
    return mData;
}

uint32_t Packet::size() const
{
    return mSize;
}

}