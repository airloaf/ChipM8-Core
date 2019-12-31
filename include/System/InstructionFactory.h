/**
 * Authors: Vikram Singh
 * File: InstructionFactory.h
 *
 * 
 **/

#pragma once

#include <cstdint>

#include "Instruction.h"

class InstructionFactory{
    public:
        /**
         * Instruction creation method.
         *
         * @param opcode - the opcode to process
         *
         * @return Instruction - the instruction
         * corresponding to the given opcode
         **/
        Instruction *createInstruction(uint16_t opcode);        

};
