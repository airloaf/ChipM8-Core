#pragma once

#include "Memory.h"
#include "Registers.h"

/**
 * "Interpreter" for Chip8
 *
 * The Interpreter is responsible for processing the Chip8 instructions.
 **/
class Interpreter{

    public:
        Interpreter();
        ~Interpreter();

        /**
         * Ticks the Interpreter for one cycle
         *
         * Each cycle the Interpreter is responsible for the following
         * responsibilities:
         * - Fetch the next instruction
         * - Process the instruction
         **/
        void tick();

        /**
         * Ticks the Sound and Delay timers
         *
         * This function should be called at a rate
         * of 60 Hz. It is separate from the
         * main tick function due to a difference
         * in clock rate.
         **/
        void tickTimers();

        /**
         * Checks if the Interpreter is currently halted
         *
         * Due to the WAIT instruction (0xFX0A), the
         * Interpreter may halt until a key is pressed.
         * This function determines if the Interpreter is
         * currently halted, waiting for input.
         **/
        bool hasExecutionHalted();

        Memory memory; // Memory for Chip8. (4KB)
        Registers registers; // Registers associated with the Interpreter
};
