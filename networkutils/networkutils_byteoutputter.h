#ifndef NETWORKUTILS_BYTEOUTPUTTER_H
#define NETWORKUTILS_BYTEOUTPUTTER_H

#include <ostream>

namespace networkutils
{

class ByteOutputter
{
public:
    ByteOutputter(const void* data, unsigned int size, int bytesPerLine = -1);

    const void* bytes() const;
    unsigned int size() const;
    int bytesPerLine() const;
private:
    const void* mBytes;
    unsigned int mSize;
    int mBytesPerLine;
};

std::ostream& operator<<(std::ostream& stream, const ByteOutputter& printer);

inline const void* ByteOutputter::bytes() const
{
    return mBytes;
}

inline unsigned int ByteOutputter::size() const
{
    return mSize;
}

inline int ByteOutputter::bytesPerLine() const
{
    return mBytesPerLine;
}

}

#endif