#include <Devices/MemoryMappedInput.h>

MemoryMappedInput::MemoryMappedInput(){
    keys[0] = 0x00;
    keys[1] = 0x00;
}

uint8_t MemoryMappedInput::read(std::size_t address){
    return keys[address];
}

void MemoryMappedInput::write(std::size_t address, uint8_t value){
    keys[address] = value;
}
