#pragma once

#include <stdint.h>

/**
 * Keypad Input
 *
 * This class represents the Chip8 keypad input.
 * The Keypad has 16 keys with Hexadecimal
 * values for its input (0x0 - 0xF).
 **/
class Input{
    public:
        /**
         * Checks if the key is pressed
         *
         * @param key - the key to check.
         **/
        bool isKeyPressed(uint8_t key);

        /**
         * Sets the key press value
         *
         * @param key - the key to check.
         * @param pressed - boolean indicating if
         * the key is pressed
         **/
        void setKeyPressed(uint8_t key, bool pressed);

    private:
        bool keys[16];

};
