
#include "basestation_networkadapter.h"
#include "basestation_arpobserver.h"

// Only used for debug observer
#include "basestation_networkobserver.h"
#include "basestation_ethernetdecoder.h"
#include "basestation_byteprinter.h"

#include <iostream>
#include <stdexcept>

namespace
{

class DebugObserver : public basestation::NetworkObserver
{
public:
    DebugObserver() {}
    void receive(basestation::NetworkAdapter* network, std::shared_ptr<const basestation::Packet> packet)
    {
        if (!packet)
        {
            throw std::runtime_error("DebugObserver got NULL packet");
        }

        std::cout << "Debug observer received packet, size = " << packet->size() << "\n";

        std::cout << "Ethernet header, " << basestation::BytePrinter(packet->data(), 14, 6) << "\n";

        basestation::EthernetDecoder decoder(packet);
        std::cout << "Ethernet fields, " << decoder << "\n";

        unsigned short type = decoder.type();
        std::cout << "type = " << basestation::BytePrinter(&type, 2) << "\n";
    }
};

}

int main(int argc, char* argv[])
{
    try
    {
        // Create network adapter
        basestation::NetworkAdapter net;
        std::cout << "Created device " << net.interface() << "\n";

        // Attach receivers
        DebugObserver debugger;
        net.attach(&debugger);

        basestation::ArpObserver arp;
        net.attach(&arp);

        while (true);
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << "Caught exception, "
                  << "what = [" << error.what() << "]"
                  << "\n";

        return -1;
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Caught unexpected exception\n";

        return -2;
    }
    
    return 0;
}