#include "networkstack_stack.h"

#include <stdexcept>
#include <cstring>
#include <iostream> // TODO: remove

#include <networkpackets_arp.h>
#include <networkpackets_arpdecoder.h>

#include <networkutils_byteoutputter.h> // TODO: remove

namespace networkstack
{

namespace
{

const uint8_t ARP_TABLE_SIZE = 255;

const networkutils::MacAddress ADDRESS_ALL = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

const uint8_t HARDWARE_ADDRESS_SIZE = 6;
const uint8_t IP_ADDRESS_SIZE = 4;

const uint16_t ETH_P_ARP = 0x0806;
const uint16_t ETHERNET_HARDWARE_TYPE = 0x0001;
const uint16_t IPV4_PROTOCOL = 0x0800;
const uint16_t ARP_REQUEST = 0x0001;
const uint16_t ARP_RESPONSE = 0x0002;

}

Stack::Stack(
    networkadapter::Adapter* adapter,
    const std::string& ipAddress,
    const networkutils::MacAddress& hardwareAddress)
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

    if (mHardwareAddress != ethernet.getMacAddress("DestinationMac") &&
        ADDRESS_ALL != ethernet.getMacAddress("DestinationMac"))
    {
        return;
    }

    switch(ethernet.getUint16("EtherType"))
    {
    case ETH_P_ARP:
        processArp(adapter, ethernet);
        break;
    default:
        // Log ?
        break;
    }
}

void Stack::processArp(
    networkadapter::Adapter* adapter,
    const networkpackets::Ethernet& packet)
{
    networkpackets::ArpDecoder decoder(packet.getPayload("Payload"));

    std::cout << "ARP Packet = " << networkutils::ByteOutputter(packet.getPacket()->data(), packet.getPacket()->size(), 8) << "\n";

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

    networkpackets::Arp arp = networkpackets::Arp::fromFullPacket(packet.getPayload("Payload"));

    std::cout << "Received ARP packet = " << arp << "\n";

    const networkutils::MacAddress macAddress = arp.getMacAddress("SourceMac");
    const uint32_t ipAddress = arp.getUint32("SourceIP");

    mArpTable.update(macAddress.value(), (const uint8_t*)&ipAddress);

    std::cout << "Destination IP = " << networkutils::IpAddress(arp.getUint32("DestinationIP")) << ", "
              << "this IP = " << mIpAddress
              << "\n";

    if (networkutils::IpAddress(arp.getUint32("DestinationIP")) == mIpAddress &&
        arp.getUint16("OpCode") == ARP_REQUEST)
    {
        arp.setUint16("OpCode", ARP_RESPONSE);
        arp.setUint32("DestinationIP", arp.getUint32("SourceIP"));
        arp.setMacAddress("DestinationMac", arp.getMacAddress("SourceMac"));
        arp.setUint32("SourceIP", mIpAddress.asInt());
        arp.setMacAddress("SourceMac", mHardwareAddress);

        networkpackets::Ethernet response = networkpackets::Ethernet::fromPayload(arp.getPacket());
        response.setMacAddress("SourceMac", mHardwareAddress);
        response.setMacAddress("DestinationMac", packet.getMacAddress("SourceMac"));
        response.setUint16("EtherType", ETH_P_ARP);

        std::cout << "Sending reply = " << arp << "\n";

        adapter->send(response.getPacket());
    }
}

}
