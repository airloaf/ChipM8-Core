#include <System/Registers.h>

#include <stdexcept>

uint8_t Registers::getVRegister(std::size_t registerNumber){
    if(registerNumber < 16){
        return V[registerNumber];
    }else{
        throw std::domain_error("Invalid register number");
    }
}

uint8_t Registers::getDelayRegister(){
    return DT;
}

uint8_t Registers::getSoundRegister(){
    return ST;
}

uint8_t Registers::getStackPointer(){
    return SP;
}

uint16_t Registers::getMemoryRegister(){
    return I;
}

uint16_t Registers::getProgramCounter(){
    return PC;
}

void Registers::setVRegister(std::size_t registerNumber, uint8_t registerValue){
    if(registerNumber < 16){
        V[registerNumber] = registerValue;
    }else{
        throw std::domain_error("Invalid register number");
    }
}

void Registers::setDelayRegister(uint8_t value){
    DT = value;
}

void Registers::setSoundRegister(uint8_t value){
    ST = value;
}

void Registers::setStackPointer(uint8_t value){
    SP = value;
}

void Registers::setMemoryRegister(uint16_t value){
    I = value;
}

void Registers::setProgramCounter(uint16_t value){
    PC = value;
}
