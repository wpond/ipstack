#ifndef NETWORKSTACK_ETHERNETDECODER_H
#define NETWORKSTACK_ETHERNETDECODER_H

#include "networkstack_packet.h"
#include "networkutils_byteoutputter.h"

#include <memory>
#include <ostream>

namespace networkstack
{

class EthernetDecoder
{
public:
    EthernetDecoder(std::shared_ptr<const Packet> packet);

    const char* destinationMac() const;
    const char* sourceMac() const;
    unsigned short type() const;
    const char* payload() const;
    unsigned int payloadSize() const;

private:
    std::shared_ptr<const Packet> mPacket;

    char mDestinationMac[6];
    char mSourceMac[6];
    unsigned short mType;
    const char* mPayload;
    unsigned int mPayloadSize;
};

inline const char* EthernetDecoder::destinationMac() const
{
    return mDestinationMac;
}

inline const char* EthernetDecoder::sourceMac() const
{
    return mSourceMac;
}

inline unsigned short EthernetDecoder::type() const
{
    return mType;
}

inline const char* EthernetDecoder::payload() const
{
    return mPayload;
}

inline unsigned int EthernetDecoder::payloadSize() const
{
    return mPayloadSize;
}

inline std::ostream& operator<<(std::ostream& stream, const EthernetDecoder& decoder)
{
    return stream << "[EthernetPacket "
                  << "source = " << networkutils::ByteOutputter(decoder.sourceMac(), 6) << ", "
                  << "destination = " << networkutils::ByteOutputter(decoder.destinationMac(), 6) << ", "
                  << "type = " << decoder.type()
                  << "]";
}

}

#endif