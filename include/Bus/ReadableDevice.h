/**
 * Author: Vikram Singh
 * File: ReadableDevice.h
 *
 * Interface for readable devices on the bus.
 *
 **/
#include <cstdint>

class ReadableDevice{
    public:
        /**
         * Read from the device at the given address
         *
         * @param address - The local address to
         * read the device from.
         *
         * @return 8 bits (1 byte) from the requested
         * address.
         **/
        virtual uint8_t read(std::size_t address)=0;
};
