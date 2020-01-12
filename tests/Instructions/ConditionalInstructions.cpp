#include <boost/test/unit_test.hpp>

#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/System/Interpreter.h"

// Alias namespace to bdata
namespace bdata = boost::unit_test::data;

struct Fixture {
    Interpreter interpreter;
};

/**
 * Conditional Instructions
 *
 * Tests the following instructions
 * Each of them are a form of conditional
 * instruction (i.e. skipping next instruction.)
 *
 * The way we determine if the interpreter
 * skips the next instruction is by checking what
 * the program is after execution. The program counter
 * should be increment following execution.
 *
 * SEI  (3XNN)
 * SNEI (4XNN) 
 * SE   (5XY0)
 * SNE  (9XY0)
 **/
BOOST_AUTO_TEST_SUITE(ConditionalInstructionTests);

static auto SEI_Opcode =           bdata::make({0x3123, 0x32FF, 0x3C11, 0x3714, 0x378C});
static auto SEI_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0C, 0x07});
static auto SEI_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto SEI_Immediate =        bdata::make({0x23, 0xFF, 0x11, 0x14, 0x8C});
static auto SEI_Expected =         bdata::make({0x202, 0x202, 0x201, 0x201, 0x201});

// SEI Data
static auto SEI_DATA = SEI_Opcode ^ SEI_RegisterX ^ SEI_RegisterXValue ^ SEI_Immediate ^ SEI_Expected;

/**
 * SEI Instruction Test
 *
 * The conditional evaluates to true when the register's value are equal to the immediate
 *
 * This test checks the following:
 * - The program counter is incremented by one if the conditional evaluates to true
 **/
BOOST_DATA_TEST_CASE_F(Fixture, SEITests, SEI_DATA, opcode, registerX, xValue, immediate, expected){
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

static auto SNEI_Opcode =           bdata::make({0x4123, 0x42FF, 0x4C11, 0x4714, 0x478C});
static auto SNEI_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0C, 0x07});
static auto SNEI_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto SNEI_Immediate =        bdata::make({0x23, 0xFF, 0x11, 0x14, 0x8C});
static auto SNEI_Expected =         bdata::make({0x201, 0x201, 0x202, 0x202, 0x202});

// SNEI Data
static auto SNEI_DATA = SNEI_Opcode ^ SNEI_RegisterX ^ SNEI_RegisterXValue ^ SNEI_Immediate ^ SNEI_Expected;

/**
 * SNEI Instruction Test
 *
 * The conditional evaluates to true when the register's value are not equal to the immediate
 *
 * This test checks the following:
 * - The program counter is incremented by one if the conditional evaluates to true
 **/
BOOST_DATA_TEST_CASE_F(Fixture, SNEITests, SNEI_DATA, opcode, registerX, xValue, immediate, expected){
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

static auto SE_Opcode =           bdata::make({0x5120, 0x52C0, 0x5B70, 0x5CE0, 0x5710});
static auto SE_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0C, 0x07});
static auto SE_RegisterY =        bdata::make({0x02, 0x0C, 0x07, 0x0E, 0x01});
static auto SE_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto SE_RegisterYValue =   bdata::make({0x23, 0xFF, 0x12, 0xC7, 0x44});
static auto SE_Expected =         bdata::make({0x202, 0x202, 0x201, 0x201, 0x201});

// SE Data
static auto SE_DATA = SE_Opcode ^ SE_RegisterX ^ SE_RegisterXValue ^ SE_RegisterY ^ SE_RegisterYValue ^ SE_Expected;

/**
 * SE Instruction Test
 *
 * The conditional evaluates to true when the registerX's value is equal to registerY's value
 *
 * This test checks the following:
 * - The program counter is incremented by one if the conditional evaluates to true
 **/
BOOST_DATA_TEST_CASE_F(Fixture, SETests, SE_DATA, opcode, registerX, xValue, registerY, yValue, expected){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Set the initial register values
    interpreter.registers.V[registerX] = xValue;
    interpreter.registers.V[registerY] = yValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the program counter is at the expected value
    BOOST_TEST(interpreter.registers.PC == expected);
}

static auto SNE_Opcode =           bdata::make({0x5120, 0x52C0, 0x5B70, 0x5CE0, 0x5710});
static auto SNE_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0C, 0x07});
static auto SNE_RegisterY =        bdata::make({0x02, 0x0C, 0x07, 0x0E, 0x01});
static auto SNE_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto SNE_RegisterYValue =   bdata::make({0x23, 0xFF, 0x12, 0xC7, 0x44});
static auto SNE_Expected =         bdata::make({0x202, 0x202, 0x201, 0x201, 0x201});

// SNE Data
static auto SNE_DATA = SNE_Opcode ^ SNE_RegisterX ^ SNE_RegisterXValue ^ SNE_RegisterY ^ SNE_RegisterYValue ^ SNE_Expected;

/**
 * SNE Instruction Test
 *
 * The conditional evaluates to true when the registerX's value is not equal to registerY's value
 *
 * This test checks the following:
 * - The program counter is incremented by one if the conditional evaluates to true
 **/
BOOST_DATA_TEST_CASE_F(Fixture, SNETests, SNE_DATA, opcode, registerX, xValue, registerY, yValue, expected){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Set the initial register values
    interpreter.registers.V[registerX] = xValue;
    interpreter.registers.V[registerY] = yValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the program counter is at the expected value
    BOOST_TEST(interpreter.registers.PC == expected);
}

BOOST_AUTO_TEST_SUITE_END();
