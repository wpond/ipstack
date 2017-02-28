
#include "basestation_network.h"
#include "basestation_networkobserver.h"

#include <iostream>
#include <stdexcept>

namespace
{

class TestObserver : public basestation::NetworkObserver
{
public:
    TestObserver() {}
    void receive(std::shared_ptr<basestation::Packet> packet)
    {
        if (packet)
        {
            std::cout << "TestObserver received packet, size = " << packet->size() << "\n";
        }
        else
        {
            throw std::runtime_error("TestObserver got NULL packet");
        }
    }
};

}

int main(int argc, char* argv[])
{
    try
    {
        // Create network adapter
        basestation::Network net;
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