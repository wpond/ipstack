#include "networkstack_arptable.h"

#include <cstring>
#include <stdexcept>

namespace networkstack
{

namespace
{

const int HARDWARE_ADDRESS_SIZE = 6;
const int IP_ADDRESS_SIZE = 4;
const int RECORD_LENGTH = HARDWARE_ADDRESS_SIZE + IP_ADDRESS_SIZE;

bool hardwareAddressesEqual(const uint8_t* addr1, const uint8_t* addr2)
{
    return memcmp(addr1, addr2, HARDWARE_ADDRESS_SIZE) == 0;
}

bool ipAddressesEqual(const uint8_t* addr1, const uint8_t* addr2)
{
    return memcmp(addr1, addr2, IP_ADDRESS_SIZE) == 0;
}

}

ArpTable::ArpTable(uint8_t size)
    : mSize(size), mTable(new uint8_t[RECORD_LENGTH * mSize]), mUsedCount(0)
{
    memset(mTable, 0, RECORD_LENGTH * mSize);
}

ArpTable::~ArpTable()
{
    delete[] mTable;
}

bool ArpTable::update(const uint8_t* hardwareAddress, const uint8_t* ipAddress)
{
    if (!hardwareAddress)
    {
        throw std::runtime_error("ArpTable passed NULL hardwareAddress");
    }

    if (!ipAddress)
    {
        throw std::runtime_error("ArpTable passed NULL ipAddress");
    }

    // Iterate through the table, looking for hardware address
    for (uint8_t i = 0; i < mUsedCount; ++i)
    {
        if (hardwareAddressesEqual(hardwareAddress, getHardwareAddress(i)))
        {
            memcpy(getIpAddress(i), ipAddress, IP_ADDRESS_SIZE);
            return false;
        }
    }

    if (mUsedCount >= mSize)
    {
        throw std::runtime_error("No remaining space in ARP table");
    }

    memcpy(getHardwareAddress(mUsedCount), hardwareAddress, HARDWARE_ADDRESS_SIZE);
    memcpy(getIpAddress(mUsedCount), ipAddress, IP_ADDRESS_SIZE);
    ++mUsedCount;
    return true;
}

bool ArpTable::lookupIpAddress(const uint8_t* hardwareAddress, uint8_t* ipAddress) const
{
    if (!hardwareAddress)
    {
        throw std::runtime_error("ArpTable passed NULL hardwareAddress");
    }

    if (!ipAddress)
    {
        throw std::runtime_error("ArpTable passed NULL ipAddress");
    }

    for (uint8_t i = 0; i < mUsedCount; ++i)
    {
        if (hardwareAddressesEqual(hardwareAddress, getHardwareAddress(i)))
        {
            memcpy(ipAddress, getIpAddress(i), IP_ADDRESS_SIZE);
            return true;
        }
    }

    return false;
}

bool ArpTable::lookupHardwareAddress(const uint8_t* ipAddress, uint8_t* hardwareAddress) const
{
    if (!hardwareAddress)
    {
        throw std::runtime_error("ArpTable passed NULL hardwareAddress");
    }

    if (!ipAddress)
    {
        throw std::runtime_error("ArpTable passed NULL ipAddress");
    }

    for (uint8_t i = 0; i < mUsedCount; ++i)
    {
        if (ipAddressesEqual(ipAddress, getIpAddress(i)))
        {
            memcpy(hardwareAddress, getHardwareAddress(i), HARDWARE_ADDRESS_SIZE);
            return true;
        }
    }

    return false;
}

uint8_t* ArpTable::getHardwareAddress(uint8_t index)
{
    return &mTable[RECORD_LENGTH * index];
}

const uint8_t* ArpTable::getHardwareAddress(uint8_t index) const
{
    return &mTable[RECORD_LENGTH * index];
}

uint8_t* ArpTable::getIpAddress(uint8_t index)
{
    return &mTable[RECORD_LENGTH * index] + HARDWARE_ADDRESS_SIZE;
}

const uint8_t* ArpTable::getIpAddress(uint8_t index) const
{
    return &mTable[RECORD_LENGTH * index] + HARDWARE_ADDRESS_SIZE;
}

}