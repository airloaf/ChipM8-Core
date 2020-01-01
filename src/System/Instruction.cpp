#include <System/Instruction.h>

void Instruction::setBus(Bus *bus){
    // Set the bus reference
    mBus = bus;
}

void Instruction::setRegisters(Registers *registers){
    // Set the registers reference
    mRegisters = registers;
}
