#ifndef NETWORKSTACK_ARPTABLE_H
#define NETWORKSTACK_ARPTABLE_H

#include <cstdint>

namespace networkstack
{

class ArpTable
{
public:
    ArpTable(uint8_t size);
    ~ArpTable();

    // Returns true if a new record was inserted
    bool update(const uint8_t* hardwareAddress, const uint8_t* ipAddress);

    // Returns true is a record was found
    bool lookupIpAddress(const uint8_t* hardwareAddress, uint8_t* ipAddress) const;
    bool lookupHardwareAddress(const uint8_t* ipAddress, uint8_t* hardwareAddress) const;

private:
    uint8_t mSize;
    uint8_t* mTable;
    uint8_t mUsedCount;

    uint8_t* getIpAddress(uint8_t index);
    const uint8_t* getIpAddress(uint8_t index) const;
    uint8_t* getHardwareAddress(uint8_t index);
    const uint8_t* getHardwareAddress(uint8_t index) const;

    ArpTable(const ArpTable& that);
    ArpTable& operator=(ArpTable rhs);
};

}

#endif