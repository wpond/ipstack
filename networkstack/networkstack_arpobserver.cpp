#include "networkstack_arpobserver.h"

namespace networkstack
{

void ArpObserver::receive(
    networkadapter::Adapter* network,
    std::shared_ptr<const Packet> packet)
{
    // do nothing
}

}