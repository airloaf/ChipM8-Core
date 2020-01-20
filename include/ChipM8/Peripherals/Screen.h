#pragma once

#include <stdint.h>

/**
 * Screen
 *
 * This class respresents the 32 x 64 (Rows x Cols) monochrome screen.
 * Each of the pixels of the display are represented by a boolean
 * value.
 **/
class Screen{
    public:
        /**
         * Sets the pixels on the screen.
         *
         * @param row - the row of the desired pixel
         * @param col - the column of the desired pixel
         * @param lit - value indicating if the pixel is lit/on
         **/
        void setPixel(uint8_t row, uint8_t col, bool lit);

        /**
         * Gets the pixel from the screen
         *
         * @param row - the row of the desired pixel
         * @param col - the column of the desired pixel
         **/
        bool getPixel(uint8_t row, uint8_t col);

        /**
         * Clears the screen, sets all the screen
         * pixels to off/false
         **/
        void clear();

    private:
        bool pixels[32][64]; // The 32 x 64 monochrome screen

};
