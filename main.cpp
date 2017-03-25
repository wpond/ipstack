
#include "basestation_networkadapter.h"
#include "basestation_networkobserver.h"

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <iomanip>

#define HEX(X) std::hex << std::setfill('0') << std::setw(2) << ((int)X & 0x000000FF) << std::dec

namespace
{

class TestObserver : public basestation::NetworkObserver
{
public:
    TestObserver() {}
    void receive(basestation::NetworkAdapter* network, std::shared_ptr<const basestation::Packet> packet)
    {
        if (!packet)
        {
            throw std::runtime_error("TestObserver got NULL packet");
        }

        std::cout << "got packet, size = " << packet->size() << "\n";
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

        // Attach receiver
        TestObserver test;
        net.attach(&test);

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