#include "networkutils_byteoutputter.h"

#include <stdexcept>
#include <iomanip>

namespace networkutils
{

ByteOutputter::ByteOutputter(const void* data, uint32_t size, int32_t bytesPerLine)
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

    const uint8_t byte = *(const uint8_t*)outputter.bytes();
    stream << "0x" << std::hex << std::setfill('0') << std::setw(2) << ((int32_t)byte & 0x000000FF) << std::dec;
    for (uint32_t i = 1; i < outputter.size(); ++i)
    {
        if (outputter.bytesPerLine() > 0 && i % outputter.bytesPerLine() == 0)
        {
            stream << "\n   ";
        }
        const uint8_t byte = *((const uint8_t*)(outputter.bytes()) + i);
        stream << " 0x" << std::hex << std::setfill('0') << std::setw(2) << ((int32_t)byte & 0x000000FF) << std::dec;
    }

    return stream;
}

}