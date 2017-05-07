#ifndef NETWORKUTILS_BYTEOUTPUTTER_H
#define NETWORKUTILS_BYTEOUTPUTTER_H

#include <ostream>
#include <cstdint>

namespace networkutils
{

class ByteOutputter
{
public:
    ByteOutputter(const void* data, uint32_t size, int32_t bytesPerLine = -1);

    const void* bytes() const;
    uint32_t size() const;
    int32_t bytesPerLine() const;
private:
    const void* mBytes;
    uint32_t mSize;
    int32_t mBytesPerLine;
};

std::ostream& operator<<(std::ostream& stream, const ByteOutputter& printer);

inline const void* ByteOutputter::bytes() const
{
    return mBytes;
}

inline uint32_t ByteOutputter::size() const
{
    return mSize;
}

inline int32_t ByteOutputter::bytesPerLine() const
{
    return mBytesPerLine;
}

}

#endif