
#include <networkadapter_kerneladapter.h>

#include <networkstack_stack.h>
#include <networkutils_macaddress.h>

// Only used for debug observer
#include <networkadapter_observer.h>
#include <networkutils_packet.h>
#include <networkutils_byteoutputter.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdint>

namespace
{

const std::string STACK_IP_ADDRESS("192.168.43.2");
const networkutils::MacAddress STACK_HARDWARE_ADDRESS = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02
};

class DebugObserver : public networkadapter::Observer
{
public:
    DebugObserver() {}
    void receive(networkadapter::Adapter* network, std::shared_ptr<networkutils::Packet> packet)
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
        networkadapter::KernelAdapter net;
        std::cout << "Created device " << net.interface() << "\n"
                  << "HW address = " << net.hardwareAddress() << "\n";

        // Attach receivers
        //DebugObserver debugger;
        //net.attach(&debugger);

        // Attach stack
        networkstack::Stack stack(&net, STACK_IP_ADDRESS, STACK_HARDWARE_ADDRESS);

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