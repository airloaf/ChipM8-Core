#include <Devices/MemoryMappedScreen.h>

MemoryMappedScreen::MemoryMappedScreen(){
    for(std::size_t screenAddress = 0; screenAddress < (SCREEN_WIDTH * SCREEN_HEIGHT / PIXELS_PER_BYTE); screenAddress++){
        screenData[screenAddress] = 0;
    }
}

uint8_t MemoryMappedScreen::read(std::size_t address){
    return screenData[address];
}

void MemoryMappedScreen::write(std::size_t address, uint8_t value){
    screenData[address] = screenData[address] ^ value;
}
