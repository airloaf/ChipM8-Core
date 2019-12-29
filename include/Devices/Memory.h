/**
 * Author: Vikram Singh
 * File: Memory.h
 *
 * Class used to represent memory banks for
 * the Chip-8 bus.
 **/

#include "../Bus/ReadableDevice.h"
#include "../Bus/WritableDevice.h"

class Memory{

    public:

        /**
         * Creates the memory bank with a given size.
         *
         * @param size - the size of the memory bank.
         **/
        Memory(std::size_t size);

        /**
         * Override of ReadableDevice::read
         *
         * Reads from the memory bank at the given address.
         *
         * @param address - the address to read the memory bank
         * at
         *
         * @return 8 bits (1 byte) from the memory bank
         **/
        uint8_t read(std::size_t address);

        /**
         * Override of WritableDevice::write
         *
         * Writes the given value to the given address
         *
         * @param address - the address to write to
         * @param value - the value to write into
         * the memory bank
         **/
        void write(std::size_t address, uint8_t value);
};
