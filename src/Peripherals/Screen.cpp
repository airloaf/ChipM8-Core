#include "Screen.h"

#include <cstddef>

void Screen::setPixel(uint8_t row, uint8_t col, bool lit){
    pixels[row][col] = lit;
}

bool Screen::getPixel(uint8_t row, uint8_t col){
    return pixels[row][col];
}

void Screen::clear(){
    for(std::size_t row = 0; row < 32; row++){
        for(std::size_t col = 0; col < 64; col++){
            pixels[row][col] = false;
        }
    }
}
