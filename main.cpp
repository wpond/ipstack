
#include "networkadapter_adapter.h"
#include "networkstack_arpobserver.h"

// Only used for debug observer
#include "networkadapter_observer.h"
#include "networkstack_ethernetdecoder.h"
#include "networkutils_byteprinter.h"

#include <iostream>
#include <stdexcept>

namespace
{

class DebugObserver : public networkadapter::Observer
{
public:
    DebugObserver() {}
    void receive(networkadapter::Adapter* network, std::shared_ptr<const networkstack::Packet> packet)
    {
        if (!packet)
        {
            throw std::runtime_error("DebugObserver got NULL packet");
        }

        std::cout << "Debug observer received packet, size = " << packet->size() << "\n";

        std::cout << "Ethernet header, " << networkutils::BytePrinter(packet->data(), 14, 6) << "\n";

        networkstack::EthernetDecoder decoder(packet);
        std::cout << "Ethernet fields, " << decoder << "\n";

        unsigned short type = decoder.type();
        std::cout << "type = " << networkutils::BytePrinter(&type, 2) << "\n";
    }
};

}

int main(int argc, char* argv[])
{
    try
    {
        // Create network adapter
        networkadapter::Adapter net;
        std::cout << "Created device " << net.interface() << "\n";

        // Attach receivers
        DebugObserver debugger;
        net.attach(&debugger);

        networkstack::ArpObserver arp;
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