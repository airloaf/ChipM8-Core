#include <Bus/Bus.h>

Bus::Bus(std::size_t addressableLength){

}

void Bus::registerReadableDevice(ReadableDevice *device, std::size_t lowerAddress, std::size_t upperAddress){

}

void Bus::registerWritableDevice(WritableDevice *device, std::size_t lowerAddress, std::size_t upperAddress){

}

uint8_t Bus::read(std::size_t address){

    return 0;
}

void Bus::write(std::size_t address, uint8_t value){

}
