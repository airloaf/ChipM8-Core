/**
 * Author: Vikram Singh
 * File: Screen.h
 *
 * Class used to represent the 64 x 32
 * monochrome screen for Chip-8.
 **/

#pragma once

#include "../Bus/ReadableDevice.h"
#include "../Bus/WritableDevice.h"

class Screen: public ReadableDevice, WritableDevice{
    public:
        /**
         * Default constructor for Screen
         *
         * Sets the screen to blank (All 0s)
         **/
        Screen();

        /**
         * Override of ReadableDevice::read
         *
         * Reads a byte (8 pixels) from the screen.
         *
         * @param address - the address to read the screen at
         *
         * @return 8 bits (8 pixels, 1 byte) from the screen
         **/
        uint8_t read(std::size_t address);

        /**
         * Override of WritableDevice::write
         *
         * Write a byte (8 pixels) to the screen.
         *
         * @param address - the address to write to on the screen
         * @param value - the value to write to
         **/
        void write(std::size_t address, uint8_t value);

    private:

};
