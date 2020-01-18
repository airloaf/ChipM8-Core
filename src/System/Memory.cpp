#include <ChipM8/System/Memory.h>

uint8_t &Memory::operator[](std::size_t index){
    return data[index];
}
