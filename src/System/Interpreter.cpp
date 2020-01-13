#include "Interpreter.h"

Interpreter::Interpreter(){
    // The program counter should start at 0x200
    registers.PC = 0x200;

    // The stack pointer should point to 0x200
    registers.SP = 0x200;

    // Set all other pointers to 0
    for(std::size_t registerNumber = 0; registerNumber < 16; registerNumber++){
        registers.V[registerNumber] = 0;
    }

    registers.DT = 0;
    registers.ST = 0;
}

Interpreter::~Interpreter(){

}

uint16_t fetchOpcode(Memory &memory, Registers &registers){
    uint16_t opcode = memory[registers.PC] << 8;
    opcode += memory[registers.PC+1];
    return opcode;
}

void CLS(){

}

void RET(){

}

void JUMP(){

}

void EXE(){

}

void SEI(Registers &registers, uint8_t registerX, uint8_t immediate){
    if(registers.V[registerX] == immediate){
        registers.PC += 2;
    }
}

void SNEI(Registers &registers, uint8_t registerX, uint8_t immediate){
    if(registers.V[registerX] != immediate){
        registers.PC += 2;
    }
}

void SE(Registers &registers, uint8_t registerX, uint8_t registerY){
    if(registers.V[registerX] == registers.V[registerY]){
        registers.PC += 2;
    }
}

void STRI(){

}

void ADDI(Registers &registers, uint8_t registerX, uint16_t immediate){
    registers.V[registerX] += immediate;
}

void COPY(Registers &registers, uint8_t registerX, uint8_t registerY){
    registers.V[registerX] = registers.V[registerY];
}

void OR(Registers &registers, uint8_t registerX, uint8_t registerY){
    registers.V[registerX] = registers.V[registerX] | registers.V[registerY];
}

void AND(Registers &registers, uint8_t registerX, uint8_t registerY){
    registers.V[registerX] = registers.V[registerX] & registers.V[registerY];
}

void XOR(Registers &registers, uint8_t registerX, uint8_t registerY){
    registers.V[registerX] = registers.V[registerX] ^ registers.V[registerY];
}

void ADD(Registers &registers, uint8_t registerX, uint8_t registerY){
    int result = registers.V[registerX] + registers.V[registerY];
    registers.V[registerX] = result;
    registers.V[0xF] = (result < 0x100)? 0: 1;
}

void SUB(Registers &registers, uint8_t registerX, uint8_t registerY){
    int result = registers.V[registerX] - registers.V[registerY];
    registers.V[registerX] = result;
    registers.V[0xF] = (result >= 0)? 0: 1;
}

void RSH(Registers &registers, uint8_t registerX, uint8_t registerY){
    registers.V[0xF] = (registers.V[registerY] & 0x01);
    registers.V[registerX] = registers.V[registerY] >> 1;
}

void SUBR(Registers &registers, uint8_t registerX, uint8_t registerY){
    int result = registers.V[registerY] - registers.V[registerX];
    registers.V[registerX] = result;
    registers.V[0xF] = (result >= 0)? 0: 1;
}

void LSH(Registers &registers, uint8_t registerX, uint8_t registerY){
    registers.V[0xF] = (registers.V[registerY] & 0x80) >> 7;
    registers.V[registerX] = registers.V[registerY] << 1;
}

void SNE(Registers &registers, uint8_t registerX, uint8_t registerY){
    if(registers.V[registerX] != registers.V[registerY]){
        registers.PC += 2;
    }
}

void STR(){

}

void BR(){

}

void RND(){

}

void DRAW(){

}

void SP(Registers &registers, Input &input, uint8_t registerX){
    uint8_t key = (registers.V[registerX] & 0x0F);
    if(input.isKeyPressed(key)){
        registers.PC += 2;
    }
}

void SNP(Registers &registers, Input &input, uint8_t registerX){
    uint8_t key = (registers.V[registerX] & 0x0F);
    if(!input.isKeyPressed(key)){
        registers.PC += 2;
    }
}

void STRD(){

}

void WAIT(Registers &registers, Input &input, uint8_t registerX){
    input.waitForKeyPress(registers, registerX);
}

void SETD(){

}

void SETS(){

}

void OFFS(){

}

void NUM(){

}

void BCD(){

}

void STRM(){

}

void LDM(){

}

void Interpreter::executeInstruction(uint16_t opcode){
    // Get certain values from the opcode
    uint8_t firstHexit =    (opcode & 0xF000) >> 12;
    uint8_t fourthHexit =   (opcode & 0x000F);
    uint8_t lsb =           (opcode & 0x00FF);
    uint8_t registerX =     (opcode & 0x0F00) >> 8;
    uint8_t registerY =     (opcode & 0x00F0) >> 4;
    uint16_t address =      (opcode & 0x0FFF);
    uint8_t immediate =     lsb;
    uint8_t nibble =        (opcode & 0x000F);
    
    // Next we need to determine which instruction is occuring
    // The first hexit can determine many of the instructions
    switch(firstHexit){
        case 0x0:
            if(opcode == 0x00EE){
                // RET
                RET();
            }else if(opcode == 0x00E0){
                // CLS
                CLS();
            }else{
                // OEXE
            }
            break;
        case 0x1:
            // JUMP
            JUMP();
            break;
        case 0x2:
            // EXE
            EXE();
            break;
        case 0x3:
            // SEI
            SEI(registers, registerX, immediate);
            break;
        case 0x4:
            // SNEI
            SNEI(registers, registerX, immediate);
            break;
        case 0x5:
            // SE
            SE(registers, registerX, registerY);
            break;
        case 0x6:
            // STRI
            STRI();
            break;
        case 0x7:
            // ADDI
            ADDI(registers, registerX, immediate);
            break;
        case 0x8:
            switch(fourthHexit){
                case 0x0:
                    // COPY
                    COPY(registers, registerX, registerY);
                    break;
                case 0x1:
                    // OR
                    OR(registers, registerX, registerY);
                    break;
                case 0x2:
                    // AND
                    AND(registers, registerX, registerY);
                    break;
                case 0x3:
                    // XOR
                    XOR(registers, registerX, registerY);
                    break;
                case 0x4:
                    // ADD
                    ADD(registers, registerX, registerY);
                    break;
                case 0x5:
                    // SUB
                    SUB(registers, registerX, registerY);
                    break;
                case 0x6:
                    // RSH
                    RSH(registers, registerX, registerY);
                    break;
                case 0x7:
                    // SUBR
                    SUBR(registers, registerX, registerY);
                    break;
                default:
                    // LSH
                    LSH(registers, registerX, registerY);
                    break;
            }
            break;
        case 0x9:
            // SNE
            SNE(registers, registerX, registerY);
            break;
        case 0xA:
            // STR
            STR();
            break;
        case 0xB:
            // BR
            BR();
            break;
        case 0xC:
            // RND
            RND();
            break;
        case 0xD:
            // DRAW
            DRAW();
            break;
        case 0xE:
            if(fourthHexit == 0xE){
                // SP
                SP(registers, input, registerX);
            }else{
                // SNP
                SNP(registers, input, registerX);
            }
            break;
        case 0xF:
            switch(lsb){
                case 0x07:
                    // STRD
                    STRD();
                    break;
                case 0x0A:
                    // WAIT
                    WAIT(registers, input, registerX);
                    break;
                case 0x15:
                    // SETD
                    SETD();
                    break;
                case 0x18:
                    // SETS
                    SETS();
                    break;
                case 0x1E:
                    // OFFS
                    OFFS();
                    break;
                case 0x29:
                    // NUM
                    NUM();
                    break;
                case 0x33:
                    // BCD
                    BCD();
                    break;
                case 0x55:
                    // STRM
                    STRM();
                    break;
                default:
                    // LDM
                    LDM();
                    break;
            }
            break;
    }
}

void Interpreter::tick(){

    // First we need to fetch the opcode
    uint16_t opcode = fetchOpcode(memory, registers);

    // Next we need to increment the program counter
    // for the next instruction.
    registers.PC += 2;

    // Execute the instruction
    executeInstruction(opcode);
}

void Interpreter::tickTimers(){
    
}

bool Interpreter::hasExecutionHalted(){
    return input.isWaiting();
}
