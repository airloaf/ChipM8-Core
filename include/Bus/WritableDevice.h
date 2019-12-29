/**
 * Author: Vikram Singh
 * File: WritableDevice.h
 *
 * Interface for writable devices on the bus.
 *
 **/
#pragma once

#include <cstdint>

class WritableDevice{
    public:
        /**
         * Write to the device at the given address
         *
         * @param address - The local address to
         * write into the device.
         * @param value - The value to write into
         * the device
         **/
        virtual void write(std::size_t address, uint8_t value)=0;
};
