/**
 * Author: Vikram Singh
 * File: MemoryMappedInput.h
 *
 * Class used to represent the keypad input
 * of the Chip-8 system. This is memory mapped
 * so reading and writing to this device modifies
 * the status of the input.
 **/
#pragma once

#include "../Bus/ReadableDevice.h"
#include "../Bus/WritableDevice.h"

class MemoryMappedInput : public ReadableDevice, WritableDevice{
    public:
        /**
         * Default constructor for Input
         *
         * Sets the input to not pressed
         * (all 16 hex keys)
         **/
        MemoryMappedInput();

        /**
         * Override of ReadableDevice::read
         *
         * Reads a byte (8 pixels) from the input.
         *
         * @param address - the address to read the input at
         *
         * @return 8 bits (8 keys, 1 byte) from the input
         **/
        uint8_t read(std::size_t address);

        /**
         * Override of WritableDevice::write
         *
         * Write a byte (8 keys) to the input.
         * The value should have only a single
         * bit corresponding to the key pressed/released.
         *
         * @param address - the address to write to on the input
         * @param value - the value to write
         **/
        void write(std::size_t address, uint8_t value);
};
