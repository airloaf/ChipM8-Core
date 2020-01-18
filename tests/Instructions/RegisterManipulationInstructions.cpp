#include <boost/test/unit_test.hpp>

#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <ChipM8/System/Interpreter.h>

// Alias namespace to bdata
namespace bdata = boost::unit_test::data;

struct Fixture {
    Interpreter interpreter;
};

/**
 * Register Manipulation Tests
 *
 * Tests the following instructions
 * Each of them involve manipulating
 * registers (storing values, or
 * copying values)
 *
 * STRI (6XNN)
 * STRD (FX07)
 * SETD (FX15)
 * SETS (FX18)
 **/
BOOST_AUTO_TEST_SUITE(RegisterManipulationTests);

static auto STRI_Opcode =       bdata::make({0x6129, 0x6FFF, 0x60CB, 0x6B14, 0x6C18});
static auto STRI_RegisterX =    bdata::make({0x01, 0x0F, 0x00, 0x0B, 0x0C});
static auto STRI_Immediate =    bdata::make({0x29, 0xFF, 0xCB, 0x14, 0x18});

// STRI Data
static auto STRI_DATA = STRI_Opcode ^ STRI_RegisterX ^ STRI_Immediate;

/**
 * STRI Instruction
 *
 * STRI Sets the value of the register to the
 * immediate value.
 *
 * This test checks the following:
 * - The register value is set to the immediate value
 **/
BOOST_DATA_TEST_CASE_F(Fixture, STRITests, STRI_DATA, opcode, registerX, immediate){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Tick the interpreter
    interpreter.tick();

    // Check that the registers value is set to the immediate value
    BOOST_TEST(interpreter.registers.V[registerX] == immediate);
}

static auto STRD_Opcode =       bdata::make({0xF107, 0xFF07, 0xF007, 0xFB07, 0xFC07});
static auto STRD_RegisterX =    bdata::make({0x01, 0x0F, 0x00, 0x0B, 0x0C});
static auto STRD_DelayValue =   bdata::make({0x29, 0xFF, 0xCB, 0x14, 0x18});

// STRD Data
static auto STRD_DATA = STRD_Opcode ^ STRD_RegisterX ^ STRD_DelayValue;

/**
 * STRD Instruction
 *
 * STRD Sets the value of a register
 * to the delay register
 *
 * This test checks the following:
 * - The register value is set to the immediate value
 **/
BOOST_DATA_TEST_CASE_F(Fixture, STRDTests, STRD_DATA, opcode, registerX, delayValue){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Set the delay register
    interpreter.registers.DT = delayValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the registers value is set to the immediate value
    BOOST_TEST(interpreter.registers.V[registerX] == delayValue);
}

static auto SETD_Opcode =       bdata::make({0xF115, 0xFF15, 0xF015, 0xFB15, 0xFC15});
static auto SETD_RegisterX =    bdata::make({0x01, 0x0F, 0x00, 0x0B, 0x0C});
static auto SETD_registerValue =   bdata::make({0x29, 0xFF, 0xCB, 0x14, 0x18});

// SETD Data
static auto SETD_DATA = SETD_Opcode ^ SETD_RegisterX ^ SETD_registerValue;

/**
 * SETD Instruction
 *
 * SETD Sets the value of the delay register
 * to the register value
 *
 * This test checks the following:
 * - The register value is set to the immediate value
 **/
BOOST_DATA_TEST_CASE_F(Fixture, SETDTests, SETD_DATA, opcode, registerX, registerValue){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Set the delay register
    interpreter.registers.V[registerX] = registerValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the delay timer register is equal to the register value
    BOOST_TEST(interpreter.registers.DT == registerValue);
}

static auto SETS_Opcode =       bdata::make({0xF118, 0xFF18, 0xF018, 0xFB18, 0xFC18});
static auto SETS_RegisterX =    bdata::make({0x01, 0x0F, 0x00, 0x0B, 0x0C});
static auto SETS_registerValue =   bdata::make({0x29, 0xFF, 0xCB, 0x14, 0x18});

// SETS Data
static auto SETS_DATA = SETS_Opcode ^ SETS_RegisterX ^ SETS_registerValue;

/**
 * SETS Instruction
 *
 * SETS Sets the value of the sound register
 * to the register value
 *
 * This test checks the following:
 * - The register value is set to the immediate value
 **/
BOOST_DATA_TEST_CASE_F(Fixture, SETSTests, SETS_DATA, opcode, registerX, registerValue){
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Set the delay register
    interpreter.registers.V[registerX] = registerValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the sound timer register is equal to the register value
    BOOST_TEST(interpreter.registers.ST == registerValue);
}

BOOST_AUTO_TEST_SUITE_END();
