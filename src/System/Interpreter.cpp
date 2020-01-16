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

    // Set the screen to all clear
    screen.clear();

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

void CLS(Screen &screen){
    screen.clear();
}

void RET(Registers &registers, Memory &memory){
    uint8_t addressUpper = memory[registers.SP+0];
    uint8_t addressLower = memory[registers.SP+1];

    uint16_t address = (addressUpper << 8) + addressLower;

    registers.PC = address;
    registers.SP += 2;
}

void JUMP(Registers &registers, uint16_t address){
    registers.PC = address;
}

void EXE(Registers &registers, Memory &memory, uint16_t address){
    uint16_t pcUpper = (registers.PC & 0xFF00) >> 8;
    uint16_t pcLower = (registers.PC & 0x00FF) >> 0;

    registers.SP -= 2;

    memory[registers.SP+0] = pcUpper;
    memory[registers.SP+1] = pcLower;

    registers.PC = address;
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

void STRI(Registers &registers, uint8_t registerX, uint16_t immediate){
    registers.V[registerX] = immediate;
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

void STR(Registers &registers, uint16_t address){
    registers.I = address;
}

void BR(Registers &registers, uint16_t address){
    registers.PC = ((address + registers.V[0]) % 0x1000);
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

void STRD(Registers &registers, uint8_t registerX){
    registers.V[registerX] = registers.DT;
}

void WAIT(Registers &registers, Input &input, uint8_t registerX){
    input.waitForKeyPress(registers, registerX);
}

void SETD(Registers &registers, uint8_t registerX){
    registers.DT = registers.V[registerX];
}

void SETS(Registers &registers, uint8_t registerX){
    registers.ST = registers.V[registerX];
}

void OFFS(Registers &registers, uint8_t registerX){
    registers.I += registers.V[registerX];
    registers.I %= 0x1000;
}

void NUM(Registers &registers, uint8_t registerX){
    registers.I = (registers.V[registerX] % 0x10) * 5;
}

void BCD(Registers &registers, Memory &memory, uint8_t registerX){
    uint8_t registerValue = registers.V[registerX];

    int firstDigit = (registerValue / 100);
    int secondDigit = ((registerValue % 100) - (registerValue % 10)) / 10;
    int thirdDigit = registerValue % 10;

    memory[registers.I+0] = firstDigit;
    memory[registers.I+1] = secondDigit;
    memory[registers.I+2] = thirdDigit;
}

void STRM(Registers &registers, Memory &memory, uint8_t registerX){
    for(std::size_t registerNum = 0; registerNum < 16; registerNum++){
        memory[registers.I + registerNum] = registers.V[registerNum];
    }
}

void LDM(Registers &registers, Memory &memory, uint8_t registerX){
    for(std::size_t registerNum = 0; registerNum < 16; registerNum++){
        registers.V[registerNum] = memory[registers.I + registerNum];
    }
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
                RET(registers, memory);
            }else if(opcode == 0x00E0){
                // CLS
                CLS(screen);
            }else{
                // OEXE
            }
            break;
        case 0x1:
            // JUMP
            JUMP(registers, address);
            break;
        case 0x2:
            // EXE
            EXE(registers, memory, address);
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
            STRI(registers, registerX, immediate);
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
            STR(registers, address);
            break;
        case 0xB:
            // BR
            BR(registers, address);
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
                    STRD(registers, registerX);
                    break;
                case 0x0A:
                    // WAIT
                    WAIT(registers, input, registerX);
                    break;
                case 0x15:
                    // SETD
                    SETD(registers, registerX);
                    break;
                case 0x18:
                    // SETS
                    SETS(registers, registerX);
                    break;
                case 0x1E:
                    // OFFS
                    OFFS(registers, registerX);
                    break;
                case 0x29:
                    // NUM
                    NUM(registers, registerX);
                    break;
                case 0x33:
                    // BCD
                    BCD(registers, memory, registerX);
                    break;
                case 0x55:
                    // STRM
                    STRM(registers, memory, registerX);
                    break;
                default:
                    // LDM
                    LDM(registers, memory, registerX);
                    break;
            }
            break;
    }
}

void Interpreter::tick(){


    // First we need to fetch the opcode
    uint16_t opcode = fetchOpcode(memory, registers);
    
    // Increment the program counter for the next instruction
    registers.PC += 2;
    registers.PC = registers.PC % 0x1000;

    // Execute the instruction
    executeInstruction(opcode);
}

void Interpreter::tickTimers(){
    
}

bool Interpreter::hasExecutionHalted(){
    return input.isWaiting();
}
