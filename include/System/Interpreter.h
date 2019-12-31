/**
 * Author: Vikram Singh
 * File: Interpreter.h
 *
 * Interface for the ChipM8 interpreter
 **/
#pragma once

#include "../Bus/Bus.h"
#include "InstructionFactory.h"
#include "Registers.h"

class Interpreter{
    public:

        /**
         * Next clock tick for the interpreter
         *
         * Chip-8 specifications requires the
         * interpreter to be updated at a rate
         * of 60Hz. This function should be
         * called at this rate.
         **/
        void tick();

    private:
        // Bus for reading and writing to devices
        Bus *mBus;

        // Chip8 Register list
        Registers *mRegisters;

        // Instruction factory for generating instructions
        InstructionFactory mInstructionFactory;
};
