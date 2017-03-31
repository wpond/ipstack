#ifndef NETWORKUTILS_BYTEPRINTER_H
#define NETWORKUTILS_BYTEPRINTER_H

#include <ostream>

namespace networkutils
{

class BytePrinter
{
public:
    BytePrinter(const void* data, unsigned int size, int bytesPerLine = -1);

    const void* bytes() const;
    unsigned int size() const;
    int bytesPerLine() const;
private:
    const void* mBytes;
    unsigned int mSize;
    int mBytesPerLine;
};

std::ostream& operator<<(std::ostream& stream, const BytePrinter& printer);

inline const void* BytePrinter::bytes() const
{
    return mBytes;
}

inline unsigned int BytePrinter::size() const
{
    return mSize;
}

inline int BytePrinter::bytesPerLine() const
{
    return mBytesPerLine;
}

}

#endif