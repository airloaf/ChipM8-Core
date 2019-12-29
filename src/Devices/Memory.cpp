#include <Devices/Memory.h>
#include <stdexcept>

Memory::Memory(std::size_t size){
    // Set the memory size value
    mMemorySize = size;

    // Allocate the memory store with size number of values
    mMemoryStore = new uint8_t[size];
}

uint8_t Memory::read(std::size_t address){
    // return value if address was in range
    if(address < mMemorySize){
        return mMemoryStore[address];
    }else{
        throw std::out_of_range("Address was out of range");
    }
}

void Memory::write(std::size_t address, uint8_t value){
    // Write value if address was in range
    if(address < mMemorySize){
        mMemoryStore[address] = value;
    }else{
        throw std::out_of_range("Address was out of range");
    }
}
