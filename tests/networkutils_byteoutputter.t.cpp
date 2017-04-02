#include <gtest/gtest.h>

#include <stdexcept>
#include <sstream>

#include <networkutils_byteoutputter.h>

TEST(ByteOutputter, Empty)
{
    char data[1] = { 0 };
    networkutils::ByteOutputter outputter(data, 0);
    ASSERT_EQ(0, outputter.size());
    ASSERT_EQ(-1, outputter.bytesPerLine());
}

TEST(ByteOutputter, NullData)
{
    ASSERT_THROW(networkutils::ByteOutputter(NULL, 0), std::runtime_error);
}

TEST(ByteOutputter, Data)
{
    char data[5] = { 1, 2, 3, 4, 5 };
    networkutils::ByteOutputter outputter(data, 5);
    ASSERT_EQ(5, outputter.size());
    ASSERT_EQ(1, ((const char*)outputter.bytes())[0]);
    ASSERT_EQ(2, ((const char*)outputter.bytes())[1]);
    ASSERT_EQ(3, ((const char*)outputter.bytes())[2]);
    ASSERT_EQ(4, ((const char*)outputter.bytes())[3]);
    ASSERT_EQ(5, ((const char*)outputter.bytes())[4]);
    ASSERT_EQ(-1, outputter.bytesPerLine());
}

TEST(ByteOutputter, OutputInline)
{
    char data[5] = { 1, 2, 3, 4, 5 };
    networkutils::ByteOutputter outputter(data, 5);
    ASSERT_EQ(5, outputter.size());
    ASSERT_EQ(1, ((const char*)outputter.bytes())[0]);
    ASSERT_EQ(2, ((const char*)outputter.bytes())[1]);
    ASSERT_EQ(3, ((const char*)outputter.bytes())[2]);
    ASSERT_EQ(4, ((const char*)outputter.bytes())[3]);
    ASSERT_EQ(5, ((const char*)outputter.bytes())[4]);
    ASSERT_EQ(-1, outputter.bytesPerLine());

    std::ostringstream oss;
    oss << outputter;
    ASSERT_EQ("0x01 0x02 0x03 0x04 0x05", oss.str());
}

TEST(ByteOutputter, OutputMultiline)
{
    char data[5] = { 1, 2, 3, 4, 5 };
    networkutils::ByteOutputter outputter(data, 5, 2);
    ASSERT_EQ(5, outputter.size());
    ASSERT_EQ(1, ((const char*)outputter.bytes())[0]);
    ASSERT_EQ(2, ((const char*)outputter.bytes())[1]);
    ASSERT_EQ(3, ((const char*)outputter.bytes())[2]);
    ASSERT_EQ(4, ((const char*)outputter.bytes())[3]);
    ASSERT_EQ(5, ((const char*)outputter.bytes())[4]);
    ASSERT_EQ(2, outputter.bytesPerLine());

    std::ostringstream expected;
    expected << "\n"
             << "    0x01 0x02\n"
             << "    0x03 0x04\n"
             << "    0x05";

    std::ostringstream actual;
    actual << outputter;
    ASSERT_EQ(expected.str(), actual.str());
}