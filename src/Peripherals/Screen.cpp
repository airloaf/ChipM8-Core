#include "Screen.h"

void Screen::setPixel(uint8_t row, uint8_t col, bool lit){
    pixels[row][col] = lit;
}

bool Screen::getPixel(uint8_t row, uint8_t col){
    return pixels[row][col];
}
