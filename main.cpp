
#include <networkadapter_adapter.h>

// Only used for debug observer
#include <networkadapter_observer.h>
#include <networkutils_packet.h>
#include <networkutils_byteoutputter.h>

#include <iostream>
#include <stdexcept>

namespace
{

class DebugObserver : public networkadapter::Observer
{
public:
    DebugObserver() {}
    void receive(networkadapter::Adapter* network, std::shared_ptr<const networkutils::Packet> packet)
    {
        if (!packet)
        {
            throw std::runtime_error("DebugObserver got NULL packet");
        }

        std::cout << "Debug observer received packet, size = " << packet->size() << "\n";

        std::cout << "Header, " << networkutils::ByteOutputter(packet->data(), 14, 6) << "\n";
    }
};

}

int main(int argc, char* argv[])
{
    try
    {
        // Create network adapter
        networkadapter::Adapter net;
        std::cout << "Created device " << net.interface() << "\n"
                  << "HW address = " << networkutils::ByteOutputter(net.hardwareAddress(), 6) << "\n";

        // Attach receivers
        DebugObserver debugger;
        net.attach(&debugger);

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