#ifndef NETWORKUTILS_PACKET_H
#define NETWORKUTILS_PACKET_H

#include <memory>
#include <cstdint>

namespace networkutils
{

class Packet
{
public:
    Packet(const uint8_t* data, uint32_t size);
    Packet(std::shared_ptr<Packet> packet, uint32_t start=0, uint32_t size=0);
    ~Packet();

    uint8_t* data();
    const uint8_t* data() const;
    uint32_t size() const;
private:
    Packet(const Packet& that);

    uint8_t* mData;
    uint32_t mSize;
    std::shared_ptr<Packet> mParent;
};

}

#endif