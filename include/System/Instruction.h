/**
 * Author: Vikram Singh
 * File: Instruction.h
 *
 * Interface for a generic Chip-8 instruction
 **/

#pragma once

#include "../Bus/Bus.h"
#include "Registers.h"

#include <string>

class Instruction{
    public:
        /**
         * Executes the instruction.
         **/
        virtual void execute() = 0;

        /**
         * Gets the mnemonic of the instruction
         *
         * @return string - the mnemonic of the instruction
         **/
        virtual std::string getMnemonic() = 0;

        /**
         * Sets the Bus reference for the instruction
         *
         * @param bus - the bus reference to use.
         **/
        void setBus(Bus *bus);

        /**
         * Sets the registers reference for the instruction
         *
         * @param registers - the registers reference to use.
         **/
        void setRegisters(Registers *registers);

    protected:
        // Bus and registers
        Bus *mBus;
        Registers *mRegisters;
};
