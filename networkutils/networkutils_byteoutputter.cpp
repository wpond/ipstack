#include "networkutils_byteoutputter.h"

#include <stdexcept>
#include <iomanip>

namespace networkutils
{

ByteOutputter::ByteOutputter(const void* data, unsigned int size, int bytesPerLine)
    : mBytes(data), mSize(size), mBytesPerLine(bytesPerLine)
{
    if (!mBytes)
    {
        throw std::runtime_error("NULL data passed to ByteOutputter");
    }
}

std::ostream& operator<<(std::ostream& stream, const ByteOutputter& outputter)
{
    if (outputter.size() == 0)
    {
        return stream << "[0 bytes]";
    }

    if (outputter.bytesPerLine() > 0)
    {
        stream << "\n    ";
    }

    const char byte = *(const char*)outputter.bytes();
    stream << "0x" << std::hex << std::setfill('0') << std::setw(2) << ((int)byte & 0x000000FF) << std::dec;
    for (unsigned int i = 1; i < outputter.size(); ++i)
    {
        if (outputter.bytesPerLine() > 0 && i % outputter.bytesPerLine() == 0)
        {
            stream << "\n   ";
        }
        const char byte = *((const char*)(outputter.bytes()) + i);
        stream << " 0x" << std::hex << std::setfill('0') << std::setw(2) << ((int)byte & 0x000000FF) << std::dec;
    }

    return stream;
}

}