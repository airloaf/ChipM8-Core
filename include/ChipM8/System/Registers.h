#pragma once

#include <stdint.h>

struct Registers{
        uint8_t V[16]; // 16 General Purpose Registers
        uint8_t DT; // Delay Timer
        uint8_t ST; // Sound Timer

        uint16_t I; // Memory Address Register
        uint16_t PC; // Program Counter
        uint16_t SP; // Stack Pointer
};
