#include <networkpackets_genericdecoder.h>

#include <sstream>
#include <cstring>

#include <arpa/inet.h>

namespace networkpackets
{

void GenericDecoder::getUint8(const std::string& name, uint8_t* value) const
{
    if (!value)
    {
        throw std::runtime_error("NULL value passed to get [uint8_t]");
    }

    FieldPair field = findPair(name);
    checkType(field, GenericDecoder::UINT8);
    *value = mPacket->data()[field.second];
}

void GenericDecoder::getInt8(const std::string& name, int8_t* value) const
{
    if (!value)
    {
        throw std::runtime_error("NULL value passed to get [int8_t]");
    }

    FieldPair field = findPair(name);
    checkType(field, GenericDecoder::INT8);
    *value = mPacket->data()[field.second];
}

void GenericDecoder::getUint16(const std::string& name, uint16_t* value) const
{
    if (!value)
    {
        throw std::runtime_error("NULL value passed to get [uint16_t]");
    }

    FieldPair field = findPair(name);
    checkType(field, GenericDecoder::UINT16);
    
    uint16_t networkValue = 0;
    memcpy(&networkValue, &mPacket->data()[field.second], sizeof(networkValue));
    *value = ntohs(networkValue);
}

void GenericDecoder::getInt16(const std::string& name, int16_t* value) const
{
    if (!value)
    {
        throw std::runtime_error("NULL value passed to get [int16_t]");
    }

    FieldPair field = findPair(name);
    checkType(field, GenericDecoder::INT16);
    
    int16_t networkValue = 0;
    memcpy(&networkValue, &mPacket->data()[field.second], sizeof(networkValue));
    *value = ntohs(networkValue);
}

void GenericDecoder::getUint32(const std::string& name, uint32_t* value) const
{
    if (!value)
    {
        throw std::runtime_error("NULL value passed to get [uint32_t]");
    }

    FieldPair field = findPair(name);
    checkType(field, GenericDecoder::UINT32);
    
    uint32_t networkValue = 0;
    memcpy(&networkValue, &mPacket->data()[field.second], sizeof(networkValue));
    *value = ntohl(networkValue);
}

void GenericDecoder::getInt32(const std::string& name, int32_t* value) const
{
    if (!value)
    {
        throw std::runtime_error("NULL value passed to get [int32_t]");
    }

    FieldPair field = findPair(name);
    checkType(field, GenericDecoder::INT32);
    
    int32_t networkValue = 0;
    memcpy(&networkValue, &mPacket->data()[field.second], sizeof(networkValue));
    *value = ntohl(networkValue);
}

void GenericDecoder::setUint8(const std::string& name, uint8_t value) const
{
    FieldPair field = findPair(name);
    checkType(field, GenericDecoder::UINT8);
    mPacket->data()[field.second] = value;
}

void GenericDecoder::setInt8(const std::string& name, int8_t value) const
{
    FieldPair field = findPair(name);
    checkType(field, GenericDecoder::INT8);
    mPacket->data()[field.second] = value;
}

void GenericDecoder::setUint16(const std::string& name, uint16_t value) const
{
    FieldPair field = findPair(name);
    checkType(field, GenericDecoder::UINT16);
    
    uint16_t networkValue = htons(value);
    memcpy(&mPacket->data()[field.second], &networkValue, sizeof(networkValue));
}

void GenericDecoder::setInt16(const std::string& name, int16_t value) const
{
    FieldPair field = findPair(name);
    checkType(field, GenericDecoder::INT16);
    
    int16_t networkValue = htons(value);
    memcpy(&mPacket->data()[field.second], &networkValue, sizeof(networkValue));
}

void GenericDecoder::setUint32(const std::string& name, uint32_t value) const
{
    FieldPair field = findPair(name);
    checkType(field, GenericDecoder::UINT32);
    
    uint32_t networkValue = htonl(value);
    memcpy(&mPacket->data()[field.second], &networkValue, sizeof(networkValue));
}

void GenericDecoder::setInt32(const std::string& name, int32_t value) const
{
    FieldPair field = findPair(name);
    checkType(field, GenericDecoder::INT32);
    
    int32_t networkValue = htonl(value);
    memcpy(&mPacket->data()[field.second], &networkValue, sizeof(networkValue));
}

std::shared_ptr<networkutils::Packet> GenericDecoder::getPayload(const std::string& name)
{
    FieldPair field = findPair(name);
    checkType(field, GenericDecoder::PAYLOAD);

    return std::shared_ptr<networkutils::Packet>(new networkutils::Packet(mPacket, field.second));
}

std::shared_ptr<networkutils::Packet> GenericDecoder::getPacket()
{
    return mPacket;
}

GenericDecoder::GenericDecoder(uint32_t size)
{
    uint8_t data[size];
    memset(data, 0, sizeof(data));
    mPacket = std::shared_ptr<networkutils::Packet>(new networkutils::Packet(data, size));
}

GenericDecoder::GenericDecoder(std::shared_ptr<networkutils::Packet> packet)
    : mPacket(packet)
{
    if (!packet)
    {
        throw std::runtime_error("NULL packetd passed to GenericDecoder");
    }
}

void GenericDecoder::addField(const std::string& name, GenericDecoder::Type type, uint32_t offset)
{
    if (offset > mPacket->size())
    {
        std::ostringstream oss;
        oss << "Cannot add field with offset outside of packet, "
            << "packet size = " << mPacket->size() << ", "
            << "offset = " << offset;
        throw std::runtime_error(oss.str());
    }

    mFields[name] = std::make_pair(type, offset);
}

GenericDecoder::FieldPair GenericDecoder::findPair(const std::string& name) const
{
    FieldMap::const_iterator it = mFields.find(name);

    if (it == mFields.end())
    {
        std::ostringstream oss;
        oss << "Failed to find field, "
            << "name = [" << name << "]";
        throw std::runtime_error(oss.str());
    }

    return it->second;
}

void GenericDecoder::checkType(const FieldPair& field, GenericDecoder::Type type) const
{
    if (field.first != type)
    {
        std::ostringstream oss;
        oss << "Unexpected type, "
            << "found " << field.first << ", "
            << "expected " << type;
        throw std::runtime_error(oss.str());
    }
}

}