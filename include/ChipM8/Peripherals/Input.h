#pragma once

#include "../System/Registers.h"

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
        Input();

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

        /**
         * Store the next keypress into registerX of the
         * given registers.
         *
         * @param registers - the register list
         * @param registerX - the register to use
         **/
        void waitForKeyPress(Registers &registers, uint8_t registerX);

        /**
         * Return if the input is waiting for
         * a key press.
         **/
        bool isWaiting();

    private:
        Registers *registers;
        uint8_t waitedRegister;
        
        bool keys[16];
        bool waiting;
};
