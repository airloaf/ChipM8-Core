/**
 * Author: Vikram Singh
 * File: Bus.h
 *
 * Interface for ChipM8 Bus
 **/
#pragma once

#include "ReadableDevice.h"
#include "WritableDevice.h"

#include <cstdint>
#include <utility>

typedef std::pair<std::size_t, std::size_t> AddressRange;

class Bus{
    public:

        /**
         * Creates a bus with a given addressable length
         *
         * @param addressableLength - the length of the bus
         * in bytes
         **/
        Bus(std::size_t addressableLength);

        /**
         * Registers a readable device onto the bus in a given address range
         *
         * @param device - the readable device to register
         * @param lowerAddress - the lower end of address ranges to register the device
         * @param upperAddress - the upper end of address ranges to register the device
         **/
        void registerReadableDevice(ReadableDevice *device, std::size_t lowerAddress, std::size_t upperAddress);

        /**
         * Registers a writable device onto the bus in a given address range
         *
         * @param device - the writable device to register
         * @param lowerAddress - the lower end of address ranges to register the device
         * @param upperAddress - the upper end of address ranges to register the device
         **/
        void registerWritableDevice(WritableDevice *device, std::size_t lowerAddress, std::size_t upperAddress);

        /**
         * Reads a byte from the given address
         *
         * @param address - the address to read from
         *
         * @return 8 bits (1 byte) from the given address
         **/
        uint8_t read(std::size_t address);

        /**
         * Write a value to the given address
         *
         * @param address - the given address to write to
         * @param value - the value to write at the given address
         **/
        void write(std::size_t address, uint8_t value);
};
