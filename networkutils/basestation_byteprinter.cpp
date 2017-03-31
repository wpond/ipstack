#include "basestation_byteprinter.h"

#include <stdexcept>
#include <iomanip>

namespace basestation
{

BytePrinter::BytePrinter(const void* data, unsigned int size, int bytesPerLine)
    : mBytes(data), mSize(size), mBytesPerLine(bytesPerLine)
{
    if (!mBytes)
    {
        throw std::runtime_error("NULL data passed to BytePrinter");
    }
}

std::ostream& operator<<(std::ostream& stream, const BytePrinter& printer)
{
    if (printer.size() == 0)
    {
        return stream << "[0 bytes]";
    }

    if (printer.bytesPerLine() > 0)
    {
        stream << "\n    ";
    }

    const char byte = *(const char*)printer.bytes();
    stream << "0x" << std::hex << std::setfill('0') << std::setw(2) << ((int)byte & 0x000000FF) << std::dec;
    for (unsigned int i = 1; i < printer.size(); ++i)
    {
        if (printer.bytesPerLine() > 0 && i % printer.bytesPerLine() == 0)
        {
            stream << "\n   ";
        }
        const char byte = *((const char*)(printer.bytes()) + i);
        stream << " 0x" << std::hex << std::setfill('0') << std::setw(2) << ((int)byte & 0x000000FF) << std::dec;
    }

    return stream;
}

}