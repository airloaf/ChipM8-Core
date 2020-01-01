/**
 * Authors: Vikram Singh
 * File: InstructionFactory.h
 *
 * 
 **/

#pragma once

#include "Instruction.h"

#include <cstdint>

class InstructionFactory{
    public:
        /**
         * Factory create method
         *
         * @param opcode - the opcode to create an instruction
         * for
         *
         * @return Instruction - the instruction corresponding
         * to the given opcode.
         **/
        Instruction *createInstruction(uint16_t opcode);
};
