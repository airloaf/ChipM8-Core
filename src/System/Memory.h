#pragma once

#include <cstddef>
#include <stdint.h>

struct Memory{
    uint8_t &operator[](std::size_t index); // Index operator

    uint8_t data[0x10000]; // The data store for memory
};
