#include <gtest/gtest.h>

#include <networkpackets_genericdecoder.h>

namespace
{

class TestDecoder : public networkpackets::GenericDecoder
{
public:
    TestDecoder()
        : networkpackets::GenericDecoder(20)
    {
        addField("unsignedByte", UINT8, 0);
        addField("signedByte", INT8, 1);
        addField("unsignedShort", UINT16, 2);
        addField("signedShort", INT16, 4);
        addField("unsignedInt", UINT32, 6);
        addField("signedInt", INT32, 10);
        addField("payload", PAYLOAD, 14);
    }

    ~TestDecoder() {}
};

} // anonymous namespace

TEST(GenericDecoder, badFieldName)
{
    TestDecoder decoder;
    ASSERT_THROW(decoder.setUint8("missing", 0xFF), std::runtime_error);
}

TEST(GenericDecoder, badFieldType)
{
    TestDecoder decoder;
    ASSERT_THROW(decoder.setInt8("unsignedByte", 0xFF), std::runtime_error);
}

TEST(GenericDecoder, unsignedByte)
{
    TestDecoder decoder;
    decoder.setUint8("unsignedByte", 0xF2);

    uint8_t value = 0;
    decoder.getUint8("unsignedByte", &value);

    ASSERT_EQ(0xF2, value);
    ASSERT_EQ(0xF2, decoder.getPacket()->data()[0]);
}

TEST(GenericDecoder, signedByte)
{
    TestDecoder decoder;
    decoder.setInt8("signedByte", 0xF2);

    int8_t value = 0;
    decoder.getInt8("signedByte", &value);

    ASSERT_EQ((int8_t)0xF2, value);
    ASSERT_EQ(0xF2, decoder.getPacket()->data()[1]);
}

TEST(GenericDecoder, unsignedShort)
{
    TestDecoder decoder;
    decoder.setUint16("unsignedShort", 0xF234);

    uint16_t value = 0;
    decoder.getUint16("unsignedShort", &value);

    ASSERT_EQ(0xF234, value);
    ASSERT_EQ(0xF2, decoder.getPacket()->data()[2]);
    ASSERT_EQ(0x34, decoder.getPacket()->data()[3]);
}

TEST(GenericDecoder, signedShort)
{
    TestDecoder decoder;
    decoder.setInt16("signedShort", 0xF234);

    int16_t value = 0;
    decoder.getInt16("signedShort", &value);

    ASSERT_EQ((int16_t)0xF234, value);
    ASSERT_EQ(0xF2, decoder.getPacket()->data()[4]);
    ASSERT_EQ(0x34, decoder.getPacket()->data()[5]);
}

TEST(GenericDecoder, unsignedInt)
{
    TestDecoder decoder;
    decoder.setUint32("unsignedInt", 0xF2345678);

    uint32_t value = 0;
    decoder.getUint32("unsignedInt", &value);

    ASSERT_EQ(0xF2345678, value);
    ASSERT_EQ(0xF2, decoder.getPacket()->data()[6]);
    ASSERT_EQ(0x34, decoder.getPacket()->data()[7]);
    ASSERT_EQ(0x56, decoder.getPacket()->data()[8]);
    ASSERT_EQ(0x78, decoder.getPacket()->data()[9]);
}

TEST(GenericDecoder, signedInt)
{
    TestDecoder decoder;
    decoder.setInt32("signedInt", 0xF2345678);

    int32_t value = 0;
    decoder.getInt32("signedInt", &value);

    ASSERT_EQ((int32_t)0xF2345678, value);
    ASSERT_EQ(0xF2, decoder.getPacket()->data()[10]);
    ASSERT_EQ(0x34, decoder.getPacket()->data()[11]);
    ASSERT_EQ(0x56, decoder.getPacket()->data()[12]);
    ASSERT_EQ(0x78, decoder.getPacket()->data()[13]);
}

TEST(GenericDecoder, payload)
{
    TestDecoder decoder;

    std::shared_ptr<networkutils::Packet> payload = decoder.getPayload("payload");

    ASSERT_EQ(6, payload->size());
    ASSERT_EQ(0, payload->data()[0]);
    ASSERT_EQ(0, payload->data()[1]);
    ASSERT_EQ(0, payload->data()[2]);
    ASSERT_EQ(0, payload->data()[3]);
    ASSERT_EQ(0, payload->data()[4]);
    ASSERT_EQ(0, payload->data()[5]);
}
