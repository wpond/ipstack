#ifndef NETWORKPACKETS_GENERICINTERFACE_H
#define NETWORKPACKETS_GENERICINTERFACE_H

#include <networkutils_packet.h>

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
    void getUint8(const std::string& name, uint8_t* value) const;
    void getInt8(const std::string& name, int8_t* value) const;
    void getUint16(const std::string& name, uint16_t* value) const;
    void getInt16(const std::string& name, int16_t* value) const;
    void getUint32(const std::string& name, uint32_t* value) const;
    void getInt32(const std::string& name, int32_t* value) const;

    void setUint8(const std::string& name, uint8_t value) const;
    void setInt8(const std::string& name, int8_t value) const;
    void setUint16(const std::string& name, uint16_t value) const;
    void setInt16(const std::string& name, int16_t value) const;
    void setUint32(const std::string& name, uint32_t value) const;
    void setInt32(const std::string& name, int32_t value) const;

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
        PAYLOAD
    };

    friend std::ostream& operator<<(std::ostream& stream, GenericInterface::Type type);

    void addField(const std::string& name, Type type, uint32_t offset);

    uint8_t* data();

    const uint8_t* data() const;

private:
    typedef std::pair<Type, uint32_t> FieldPair;
    typedef std::map<std::string, FieldPair> FieldMap;

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
        case GenericInterface::PAYLOAD:
            return stream << "PAYLOAD";
        default:
            return stream << "UNKNOWN";
    }
}

}

#endif