#include "networkstack_stack.h"

#include <stdexcept>
#include <cstring>
#include <iostream> // TODO: remove

#include <networkpackets_ethernet.h>
#include <networkpackets_arp.h>
#include <networkpackets_arpdecoder.h>

#include <networkutils_byteoutputter.h> // TODO: remove

namespace networkstack
{

namespace
{

const uint8_t ARP_TABLE_SIZE = 255;

const uint8_t ADDRESS_ALL[6] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

const uint8_t HARDWARE_ADDRESS_SIZE = 6;
const uint8_t IP_ADDRESS_SIZE = 4;

const uint16_t ETH_P_ARP = 0x0806;
const uint16_t ETHERNET_HARDWARE_TYPE = 0x0001;
const uint16_t IPV4_PROTOCOL = 0x0800;

}

Stack::Stack(
    networkadapter::Adapter* adapter,
    const std::string& ipAddress,
    const uint8_t* hardwareAddress)
    : mAdapter(adapter),
      mIpAddress(ipAddress),
      mHardwareAddress(hardwareAddress),
      mArpTable(ARP_TABLE_SIZE)
{
    if (!mAdapter)
    {
        throw std::runtime_error("Passed NULL adapter to stack");
    }
    
    mAdapter->attach(this);
}

Stack::~Stack()
{
    mAdapter->detatch(this);
}

void Stack::receive(
    networkadapter::Adapter* adapter,
    std::shared_ptr<networkutils::Packet> packet)
{
    if (adapter != mAdapter)
    {
        return;
    }

    if (!packet)
    {
        throw std::runtime_error("Stack received NULL packet");
    }

    networkpackets::Ethernet ethernet =
        networkpackets::Ethernet::fromFullPacket(packet);

    if (memcmp(mHardwareAddress, ethernet.destinationMac(), HARDWARE_ADDRESS_SIZE) &&
        memcmp(ADDRESS_ALL, ethernet.destinationMac(), HARDWARE_ADDRESS_SIZE))
    {
        return;
    }

    switch(ethernet.getUint16("EtherType"))
    {
    case ETH_P_ARP:
        processArp(adapter, ethernet.getPayload("Payload"));
        break;
    default:
        // Log ?
        break;
    }
}

void Stack::processArp(
    networkadapter::Adapter* adapter,
    std::shared_ptr<networkutils::Packet> packet)
{
    networkpackets::ArpDecoder decoder(packet);

    std::cout << "ARP Packet = " << networkutils::ByteOutputter(packet->data(), packet->size(), 8) << "\n";

    if (decoder.hardwareType() != ETHERNET_HARDWARE_TYPE)
    {
        std::cerr << "Unsupported hardware type, "
                  << "expected = " << ETHERNET_HARDWARE_TYPE << ", "
                  << "actual = " << decoder.hardwareType()
                  << "\n";
        return;
    }

    if (decoder.protocolType() != IPV4_PROTOCOL)
    {
        std::cerr << "Unsupported protocol type, "
                  << "expected = " << IPV4_PROTOCOL << ", "
                  << "actual = " << decoder.protocolType()
                  << "\n";
        return;
    }

    if (decoder.hardwareSize() != HARDWARE_ADDRESS_SIZE)
    {
        std::cerr << "Unsupported hardware size, "
                  << "expected = " << HARDWARE_ADDRESS_SIZE << ", "
                  << "actual = " << decoder.hardwareSize()
                  << "\n";
        return;
    }

    if (decoder.protocolSize() != IP_ADDRESS_SIZE)
    {
        std::cerr << "Unsupported IP size, "
                  << "expected = " << IP_ADDRESS_SIZE << ", "
                  << "actual = " << decoder.protocolSize()
                  << "\n";
        return;
    }

    networkpackets::Arp arp = networkpackets::Arp::fromFullPacket(packet);

    std::cout << "Received ARP packet = " << arp << "\n";
}

}
