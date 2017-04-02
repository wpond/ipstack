#include "networkstack_arpobserver.h"

namespace networkstack
{

void ArpObserver::receive(
    networkadapter::Adapter* network,
    std::shared_ptr<const networkutils::Packet> packet)
{
    // do nothing
}

}