#include <boost/test/unit_test.hpp>

#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../../src/System/Interpreter.h"

#include <vector>

// Alias namespace to bdata
namespace bdata = boost::unit_test::data;


struct Fixture {
    void setup(){
        std::vector<bool> keysPressed = {true, false, false, true, true, true, false, true, false, true, false, false, false, true, false, false};
        for(std::size_t key = 0; key < 16; key++){
            interpreter.input.setKeyPressed(key, keysPressed[key]);
        }
    }

    Interpreter interpreter;
};

/**
 * Input Tests
 *
 * Tests the following instructions
 * Each of them involve usage of the input
 * object
 *
 * CLS  (00E0)
 * DRAW (DXYN)
 **/
BOOST_AUTO_TEST_SUITE(InputTests);

/**
 * CLS Instruction Test
 *
 * Sets all the pixels on the screen to off
 *
 * This test checks the following:
 * - The pixels in the screen are set to off (0).
 *
 **/
BOOST_FIXTURE_TEST_CASE(CLSInstruction, Fixture){
    uint16_t opcode = 0x00E0;
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Tick the interpreter
    interpreter.tick();

    // Check each pixel is set 
    for(std::size_t row = 0; row < 32; row++){
        for(std::size_t col = 0; col < 64; col++){
            BOOST_TEST(!interpreter.screen.getPixel(row, col));
        }
    }

}

BOOST_AUTO_TEST_SUITE_END();
