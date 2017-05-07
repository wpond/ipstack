#ifndef NETWORKPACKETS_GENERICDECODER_H
#define NETWORKPACKETS_GENERICDECODER_H

#include <networkutils_packet.h>

#include <cstdint>
#include <memory>
#include <map>
#include <string>
#include <stdexcept>
#include <ostream>

namespace networkpackets
{

class GenericDecoder
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

    std::shared_ptr<networkutils::Packet> getPayload(const std::string& name);
    std::shared_ptr<networkutils::Packet> getPacket();

protected:
    GenericDecoder(uint32_t size);
    GenericDecoder(std::shared_ptr<networkutils::Packet> packet);
    virtual ~GenericDecoder() {}

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

    friend std::ostream& operator<<(std::ostream& stream, GenericDecoder::Type type);

    void addField(const std::string& name, Type type, uint32_t offset);

private:
    typedef std::pair<Type, uint32_t> FieldPair;
    typedef std::map<std::string, FieldPair> FieldMap;

    FieldPair findPair(const std::string& name) const;
    void checkType(const FieldPair& field, Type type) const;

    std::shared_ptr<networkutils::Packet> mPacket;
    FieldMap mFields;
};

inline std::ostream& operator<<(std::ostream& stream, GenericDecoder::Type type)
{
    switch (type)
    {
        case GenericDecoder::INT8:
            return stream << "INT8";
        case GenericDecoder::UINT8:
            return stream << "UINT8";
        case GenericDecoder::INT16:
            return stream << "INT16";
        case GenericDecoder::UINT16:
            return stream << "UINT16";
        case GenericDecoder::INT32:
            return stream << "INT32";
        case GenericDecoder::UINT32:
            return stream << "UINT32";
        case GenericDecoder::PAYLOAD:
            return stream << "PAYLOAD";
        default:
            return stream << "UNKNOWN";
    }
}

}

#endif