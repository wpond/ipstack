#include "basestation_packet.h"

#include <cstring>

namespace basestation
{

Packet::Packet(const char* data, int size)
    : mSize(size)
{
    mData = new char[size];
    memcpy(mData, data, size);
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