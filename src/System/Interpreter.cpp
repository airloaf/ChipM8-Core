#include <System/Interpreter.h>

void Interpreter::tick(){

}

void Interpreter::setBus(Bus *bus){
    mBus = bus;
}

void Interpreter::setRegisters(Registers *registers){
    mRegisters = registers;
}
