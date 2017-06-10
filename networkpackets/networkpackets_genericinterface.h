#ifndef NETWORKPACKETS_GENERICINTERFACE_H
#define NETWORKPACKETS_GENERICINTERFACE_H

#include <networkutils_packet.h>
#include <networkutils_byteoutputter.h>
#include <networkutils_macaddress.h>

#include <cstdint>
#include <memory>
#include <map>
#include <string>
#include <stdexcept>
#include <ostream>

namespace networkpackets
{

class GenericInterface
{
public:
    uint8_t getUint8(const std::string& name) const;
    int8_t getInt8(const std::string& name) const;
    uint16_t getUint16(const std::string& name) const;
    int16_t getInt16(const std::string& name) const;
    uint32_t getUint32(const std::string& name) const;
    int32_t getInt32(const std::string& name) const;
    networkutils::MacAddress getMacAddress(const std::string& name) const;

    void setUint8(const std::string& name, uint8_t value) const;
    void setInt8(const std::string& name, int8_t value) const;
    void setUint16(const std::string& name, uint16_t value) const;
    void setInt16(const std::string& name, int16_t value) const;
    void setUint32(const std::string& name, uint32_t value) const;
    void setInt32(const std::string& name, int32_t value) const;
    void setMacAddress(const std::string& name, const networkutils::MacAddress& value) const;

    std::shared_ptr<networkutils::Packet> getPayload(const std::string& name) const;
    std::shared_ptr<networkutils::Packet> getPacket() const;

protected:
    GenericInterface(uint32_t size);
    GenericInterface(std::shared_ptr<networkutils::Packet> packet);
    virtual ~GenericInterface() {}

    enum Type
    {
        INT8,
        UINT8,
        INT16,
        UINT16,
        INT32,
        UINT32,
        MACADDRESS,
        PAYLOAD
    };

    friend std::ostream& operator<<(std::ostream& stream, GenericInterface::Type type);

    void addField(const std::string& name, Type type, uint32_t offset);

    uint8_t* data();

    const uint8_t* data() const;

private:
    typedef std::pair<Type, uint32_t> FieldPair;
    typedef std::map<std::string, FieldPair> FieldMap;

    friend std::ostream& operator<<(std::ostream& stream, const GenericInterface& interface);

    void getUint8(const std::string& name, uint8_t* value) const;
    void getInt8(const std::string& name, int8_t* value) const;
    void getUint16(const std::string& name, uint16_t* value) const;
    void getInt16(const std::string& name, int16_t* value) const;
    void getUint32(const std::string& name, uint32_t* value) const;
    void getInt32(const std::string& name, int32_t* value) const;
    void getMacAddress(const std::string& name, networkutils::MacAddress* value) const;

    FieldPair findPair(const std::string& name) const;
    void checkType(const FieldPair& field, Type type) const;

    std::shared_ptr<networkutils::Packet> mPacket;
    FieldMap mFields;
};

inline std::ostream& operator<<(std::ostream& stream, GenericInterface::Type type)
{
    switch (type)
    {
        case GenericInterface::INT8:
            return stream << "INT8";
        case GenericInterface::UINT8:
            return stream << "UINT8";
        case GenericInterface::INT16:
            return stream << "INT16";
        case GenericInterface::UINT16:
            return stream << "UINT16";
        case GenericInterface::INT32:
            return stream << "INT32";
        case GenericInterface::UINT32:
            return stream << "UINT32";
        case GenericInterface::MACADDRESS:
            return stream << "MACADDRESS";
        case GenericInterface::PAYLOAD:
            return stream << "PAYLOAD";
        default:
            return stream << "UNKNOWN";
    }
}

inline std::ostream& operator<<(std::ostream& stream, const GenericInterface& interface)
{
    stream << "[";
    for (GenericInterface::FieldMap::const_iterator it = interface.mFields.begin();
        it != interface.mFields.end();
        ++it)
    {
        stream << " " << it->second.first << " " << it->first << " = ";
        switch (it->second.first)
        {
        case GenericInterface::INT8:
            stream << "[ " << networkutils::ByteOutputter(interface.mPacket->data() + it->second.second, 1) << " "
                   << "(" << (uint32_t)interface.getInt8(it->first) << ") ]";
            break;
        case GenericInterface::UINT8:
            stream << "[ " << networkutils::ByteOutputter(interface.mPacket->data() + it->second.second, 1) << " "
                   << "(" << (uint32_t)interface.getUint8(it->first) << ") ]";
            break;
        case GenericInterface::INT16:
            stream << "[ " << networkutils::ByteOutputter(interface.mPacket->data() + it->second.second, 2) << " "
                   << "(" << interface.getInt16(it->first) << ") ]";
            break;
        case GenericInterface::UINT16:
            stream << "[ " << networkutils::ByteOutputter(interface.mPacket->data() + it->second.second, 2) << " "
                   << "(" << interface.getUint16(it->first) << ") ]";
            break;
        case GenericInterface::INT32:
            stream << "[ " << networkutils::ByteOutputter(interface.mPacket->data() + it->second.second, 4) << " "
                   << "(" << interface.getInt32(it->first) << ") ]";
            break;
        case GenericInterface::UINT32:
            stream << "[ " << networkutils::ByteOutputter(interface.mPacket->data() + it->second.second, 4) << " "
                   << "(" << interface.getUint32(it->first) << ") ]";
            break;
        case GenericInterface::MACADDRESS:
            stream << "[ " << interface.getMacAddress(it->first) << " ]";
            break;
        case GenericInterface::PAYLOAD:
            {
                uint32_t size = interface.mPacket->size() - it->second.second;
                stream << "[ " << networkutils::ByteOutputter(interface.mPacket->data() + it->second.second, size, 4) << " ]";
            }
            break;
        default:
            stream << "UNKNOWN";
        }
    }
    return stream << " ]";
}

}

#endif