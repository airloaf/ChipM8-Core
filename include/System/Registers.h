/**
 * Author: Vikram Singh
 * File: Registers.h
 *
 * Interface for Chip8 registers
 **/
#pragma once

#include <cstdint>

class Registers{
    public:
        /**
         * Get the general purpose register value of the
         * corresponding register.
         *
         * @param registerNumber - the register to get
         *
         * @return the register value
         **/
        uint8_t getVRegister(std::size_t registerNumber);

        /**
         * Get the delay timer register value
         *
         * @return the value of the delay timer register
         **/
        uint8_t getDelayRegister();

        /**
         * Get the sound timer register value
         *
         * @return the value of the sound timer register
         **/
        uint8_t getSoundRegister();

        /**
         * Get the stack pointer value
         *
         * @return the value of the stack pointer
         **/
        uint8_t getStackPointer();

        /**
         * Get the memory address register value
         *
         * @return the value of the memory address register
         **/
        uint16_t getMemoryRegister();

        /**
         * Get the program counter value
         *
         * @return the value of the program counter
         **/
        uint16_t getProgramCounter();

        /**
         * Set the value of the corresponding general purpose register
         *
         * @param register number - the general purpose register
         * @param register value - the value to set the register to
         **/
        void setVRegister(std::size_t registerNumber, uint8_t registerValue);

        /**
         * Set the value of the delay timer register
         *
         * @param value - the value to set the delay timer to
         **/
        void setDelayRegister(uint8_t value);

        /**
         * Set the value of the sound timer register
         *
         * @param value - the value to set the sound timer to
         **/
        void setSoundRegister(uint8_t value);

        /**
         * Set the value of the stack pointer register
         *
         * @param value - the value to set the stack pointer to
         **/
        void setStackPointer(uint8_t value);

        /**
         * Set the value of the memory address register register
         *
         * @param value - the value to set the memory address register to
         **/
        void setMemoryRegister(uint16_t value);

        /**
         * Set the value of the program counter register
         *
         * @param value - the value to set the program counter to
         **/
        void setProgramCounter(uint16_t value);
};
