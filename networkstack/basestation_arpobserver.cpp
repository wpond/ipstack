#include "basestation_arpobserver.h"

namespace basestation
{

void ArpObserver::receive(
    basestation::NetworkAdapter* network,
    std::shared_ptr<const basestation::Packet> packet)
{
    // do nothing
}

}