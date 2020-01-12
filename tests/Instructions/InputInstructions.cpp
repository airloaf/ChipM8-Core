#include <boost/test/unit_test.hpp>

#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/System/Interpreter.h"

#include <vector>

// Alias namespace to bdata
namespace bdata = boost::unit_test::data;


struct Fixture {
    Fixture(){
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
 * SP   (EX9E)
 * SNP  (EXA1) 
 * WAIT (FX0A)
 **/
BOOST_AUTO_TEST_SUITE(InputTests);

static auto SP_Opcode =           bdata::make({0xE19E, 0xE29E, 0xEB9E, 0xEC9E, 0xE79E});
static auto SP_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0C, 0x07});
static auto SP_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto SP_Expected =         bdata::make({0x202, 0x202, 0x201, 0x201, 0x201});

// SP Data
static auto SP_DATA = (SP_Opcode ^ SP_RegisterX ^ SP_RegisterXValue ^ SP_Expected);

/**
 * SP Instruction Test
 *
 * The conditional evaluates to true when key corresponding to the registers value
 * is pressed.
 *
 * This test checks the following:
 * - The program counter is incremented by one if the conditional evaluates to true
 **/
BOOST_DATA_TEST_CASE_F(Fixture, SPTests, SP_DATA, opcode, registerX, xValue, expected){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Set the initial register values
    interpreter.registers.V[registerX] = xValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the program counter is at the expected value
    BOOST_TEST(interpreter.registers.PC == expected);
}

static auto SNP_Opcode =           bdata::make({0xE1A1, 0xE2A1, 0xEBA1, 0xECA1, 0xE7A1});
static auto SNP_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0C, 0x07});
static auto SNP_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto SNP_Expected =         bdata::make({0x201, 0x201, 0x202, 0x202, 0x202});

// SNP Data
static auto SNP_DATA = (SNP_Opcode ^ SNP_RegisterX ^ SNP_RegisterXValue ^ SNP_Expected);

/**
 * SNP Instruction Test
 *
 * The conditional evaluates to true when key corresponding to the registers value
 * is not pressed.
 *
 * This test checks the following:
 * - The program counter is incremented by one if the conditional evaluates to true
 **/
BOOST_DATA_TEST_CASE_F(Fixture, SNPTests, SNP_DATA, opcode, registerX, xValue, expected){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Set the initial register values
    interpreter.registers.V[registerX] = xValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the program counter is at the expected value
    BOOST_TEST(interpreter.registers.PC == expected);
}

static auto WAIT_Opcode =           bdata::make({0xF10A, 0xF20A, 0xFB0A, 0xFC0A, 0xF70A});
static auto WAIT_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0C, 0x07});
static auto WAIT_Expected =         bdata::make({0x02, 0x0F, 0x0C, 0x0A, 0x07});

// WAIT Data
static auto WAIT_DATA = (WAIT_Opcode ^ WAIT_RegisterX ^ WAIT_Expected);

/**
 * WAIT Instruction Test
 *
 * The conditional evaluates to true when key corresponding to the registers value
 * is not pressed.
 *
 * This test checks the following:
 * - The program counter is incremented by one if the conditional evaluates to true
 **/
BOOST_DATA_TEST_CASE_F(Fixture, WAITTests, WAIT_DATA, opcode, registerX, expected){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Tick the interpreter
    interpreter.tick();

    // Execution should have halted
    BOOST_TEST(interpreter.hasExecutionHalted());

    // Set that key to be pressed
    interpreter.input.setKeyPressed(expected, true);

    // Check that the program counter is at the expected value
    BOOST_TEST(interpreter.registers.V[registerX] == expected);
}

BOOST_AUTO_TEST_SUITE_END();
