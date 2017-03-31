#include "networkstack_ethernetdecoder.h"

#include <stdexcept>
#include <cstring>

#include <arpa/inet.h>

namespace networkstack
{

EthernetDecoder::EthernetDecoder(std::shared_ptr<const Packet> packet)
    : mPacket(packet)
{
    if (!mPacket)
    {
        throw std::runtime_error("NULL packet passed to ethernet decoder");
    }

    memcpy(mDestinationMac, mPacket->data() + 0, 6);
    memcpy(mSourceMac, mPacket->data() + 6, 6);
    mType = ntohs(*mPacket->data() + 12);
    mPayload = mPacket->data() + 14;
    mPayloadSize = mPacket->size() - 14;
}

}