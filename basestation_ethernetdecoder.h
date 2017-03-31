#ifndef BASESTATION_ETHERNETDECODER_H
#define BASESTATION_ETHERNETDECODER_H

#include "basestation_packet.h"
#include "basestation_byteprinter.h"

#include <memory>
#include <ostream>

namespace basestation
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
                  << "source = " << BytePrinter(decoder.sourceMac(), 6) << ", "
                  << "destination = " << BytePrinter(decoder.destinationMac(), 6) << ", "
                  << "type = " << decoder.type()
                  << "]";
}

}

#endif