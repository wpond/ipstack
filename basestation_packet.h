#ifndef BASESTATION_PACKET_H
#define BASESTATION_PACKET_H

namespace basestation
{

class Packet
{
public:
    Packet(const char* data, int size);
    ~Packet();

    const char* data() const;
    int size() const;
private:
    char* mData;
    int mSize;
};

}

#endif