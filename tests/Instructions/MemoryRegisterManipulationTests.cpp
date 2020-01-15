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
 * Memory Register Manipulation Tests
 *
 * Tests the following instructions
 * Each of them involve manipulating
 * the memory register, I.
 *
 * STR  (ANNN)
 * OFFS (FX1E)
 * NUM  (FX29)
 * BCD  (FX33)
 * STRM (FX55)
 * LDM  (FX65)
 **/
BOOST_AUTO_TEST_SUITE(MemoryRegisterManipulationTests);

static auto STR_Opcode =       bdata::make({0xA000, 0xAFFF, 0xADAD, 0xABAD, 0xACA7});
static auto STR_Address =      bdata::make({0x0000, 0x0FFF, 0x0DAD, 0x0BAD, 0x0CA7});

// STR Data
static auto STR_DATA = STR_Opcode ^ STR_Address;

/**
 * STR Instruction
 *
 * STR Sets the value of the memory register to the
 * given address
 *
 * This test checks the following:
 * - The memory address register is set properly
 **/
BOOST_DATA_TEST_CASE_F(Fixture, STRTests, STR_DATA, opcode, address){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Tick the interpreter
    interpreter.tick();

    // Check that the registers value is set to the immediate value
    BOOST_TEST(interpreter.registers.I == address);
}

static auto OFFS_Opcode =       bdata::make({0xF11E, 0xFF1E, 0xFD1E, 0xF61E, 0xF91E});
static auto OFFS_Address =      bdata::make({0x0000, 0x0FFF, 0x0DAD, 0x0BAD, 0x0CA7});
static auto OFFS_RegisterX =    bdata::make({0x0001, 0x000F, 0x000D, 0x0006, 0x0009});
static auto OFFS_Immediate =    bdata::make({0x0020, 0x00FF, 0x0044, 0x00CC, 0x00A7});
static auto OFFS_Expected =     bdata::make({0x0020, 0x00FE, 0x0DF1, 0x0C79, 0x0D4E});

// OFFS Data
static auto OFFS_DATA = OFFS_Opcode ^ OFFS_Address ^ OFFS_RegisterX ^ OFFS_Immediate ^ OFFS_Expected;

/**
 * OFFS Instruction
 *
 * OFFS instruction adds the register value to the memory address register
 *
 * This test checks the following:
 * - The memory address register is incremented with the value
 *   of the register
 **/
BOOST_DATA_TEST_CASE_F(Fixture, OFFSTests, OFFS_DATA, opcode, address, registerX, immediate, expected){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    interpreter.registers.I = address;
    interpreter.registers.V[registerX] = immediate;

    // Tick the interpreter
    interpreter.tick();

    // Check that the registers value is set to the immediate value
    BOOST_TEST(interpreter.registers.I == expected);
}

static auto NUM_Opcode =       bdata::make({0xF129, 0xFF29, 0xFD29, 0xF629, 0xF929});
static auto NUM_RegisterX =    bdata::make({0x0001, 0x000F, 0x000D, 0x0006, 0x0009});
static auto NUM_Immediate =    bdata::make({0x0020, 0x00FF, 0x0044, 0x00CC, 0x00A7});
static auto NUM_Expected =     bdata::make({0x0000, 0x0046, 0x0014, 0x0030, 0x0023});

// NUM Data
static auto NUM_DATA = NUM_Opcode ^ NUM_RegisterX ^ NUM_Immediate ^ NUM_Expected;

/**
 * NUM Instruction
 *
 * NUM instruction will set the memory register to point to the
 * hexadecimal number in memory.
 *
 * This test checks the following:
 * - The memory address register is pointing to the correct
 *   hexadecimal digit.
 **/
BOOST_DATA_TEST_CASE_F(Fixture, NUMTests, NUM_DATA, opcode, registerX, immediate, expected){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    interpreter.registers.V[registerX] = immediate;

    // Tick the interpreter
    interpreter.tick();

    // Check that the registers value is set to the immediate value
    BOOST_TEST(interpreter.registers.I == expected);
}

static auto BCD_Opcode =       bdata::make({0xF133, 0xFF33, 0xFD33, 0xF633, 0xF933});
static auto BCD_Address =      bdata::make({0x0001, 0x000F, 0x000D, 0x0006, 0x0009});
static auto BCD_RegisterX =    bdata::make({0x0001, 0x000F, 0x000D, 0x0006, 0x0009});
static auto BCD_Immediate =    bdata::make({   123,     34,      0,    255,      3});
static auto BCD_Expected1 =    bdata::make({     1,      0,      0,      2,      0});
static auto BCD_Expected2 =    bdata::make({     2,      3,      0,      5,      0});
static auto BCD_Expected3 =    bdata::make({     3,      4,      0,      5,      3});

// BCD Data
static auto BCD_DATA = BCD_Opcode ^ BCD_Address ^ BCD_RegisterX ^ BCD_Immediate ^ BCD_Expected1 ^ BCD_Expected2 ^ BCD_Expected3;

/**
 * BCD Instruction
 *
 * BCD instruction will set the next three values in memory
 * starting at the memory address register to have the decimal
 * digits of the given register.
 *
 * This test checks the following:
 * - The three digits are properly stored in memory
 **/
BOOST_DATA_TEST_CASE_F(Fixture, BCDTests, BCD_DATA, opcode, address, registerX, immediate, digit1, digit2, digit3){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Set the address register
    interpreter.registers.I = address;

    // Set the register value
    interpreter.registers.V[registerX] = immediate;

    // Tick the interpreter
    interpreter.tick();

    // Check that the digits are stored in memory
    BOOST_TEST(interpreter.memory[interpreter.registers.I+0] == digit1);
    BOOST_TEST(interpreter.memory[interpreter.registers.I+1] == digit2);
    BOOST_TEST(interpreter.memory[interpreter.registers.I+2] == digit3);
}

/**
 * STRM Instruction
 *
 * STRM instruction will set the next three values in memory
 * starting at the memory address register to have the decimal
 * digits of the given register.
 *
 * This test checks the following:
 * - The three digits are properly stored in memory
 **/
BOOST_DATA_TEST_CASE_F(Fixture, STRMTest1){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Set the address register
    interpreter.registers.I = address;

    // Set the register value
    interpreter.registers.V[registerX] = immediate;

    // Tick the interpreter
    interpreter.tick();

    // Check that the digits are stored in memory
    BOOST_TEST(interpreter.memory[interpreter.registers.I+0] == digit1);
    BOOST_TEST(interpreter.memory[interpreter.registers.I+1] == digit2);
    BOOST_TEST(interpreter.memory[interpreter.registers.I+2] == digit3);
}

BOOST_AUTO_TEST_SUITE_END();