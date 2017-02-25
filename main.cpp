
#include "basestation_network.h"

#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
    try
    {
        // Create network adapter
        basestation::Network net;
        std::cout << "Created device " << net.interface() << "\n";

        // Attach stack
        

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