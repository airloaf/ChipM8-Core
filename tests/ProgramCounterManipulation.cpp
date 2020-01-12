#include <boost/test/unit_test.hpp>

#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/System/Interpreter.h"

#include <vector>

// Alias namespace to bdata
namespace bdata = boost::unit_test::data;

struct Fixture {
    Interpreter interpreter;
};

/**
 * Program Counter Manipulation Tests
 *
 * Tests the following instructions
 * Each of them involve the program
 * counter being manipulated.
 *
 * RET  (00EE)
 * JUMP (1NNN) 
 * EXE  (2NNN)
 * BR   (BNNN)
 **/
BOOST_AUTO_TEST_SUITE(ProgramCounterManipulationTests);

static auto RET_address =      bdata::make({0x329, 0xFFF, 0x5CB, 0xB14, 0x118});

// RET Data
static auto RET_DATA = RET_address;

/**
 * RET Instruction
 *
 * RET instruction sets the program counter to whatever the following
 * two bytes in the stack are. It also incremnets the stack by 2.
 *
 * This test checks the following:
 * - The program counter is set to the address
 * - The stack pointer is incremented by 2
 **/
BOOST_DATA_TEST_CASE_F(Fixture, RETTests, RET_DATA, address){
    // Set the opcode
    interpreter.memory[0x200] = 0x00EE;

    // Put the address onto the stack
    interpreter.memory[0x1FE] = (address & 0xFF00) >> 8;
    interpreter.memory[0x1FF] = (address & 0x00FF) >> 0;

    // Set the stack to 0x1FE
    interpreter.registers.SP = 0x1FE;

    // Tick the interpreter
    interpreter.tick();

    // Check that the program counter is at the expected value
    BOOST_TEST(interpreter.registers.PC == address);
    // Check that the stack pointer is incremented by 2
    BOOST_TEST(interpreter.registers.SP == 0x200);
}

static auto JUMP_opcode=        bdata::make({0x1329, 0x1FFF, 0x15CB, 0x1B14, 0x1118});
static auto JUMP_address =      bdata::make({0x329, 0xFFF, 0x5CB, 0xB14, 0x118});

// JUMP Data
static auto JUMP_DATA = JUMP_opcode ^ JUMP_address;

/**
 * JUMP Instruction
 *
 * JUMP instruction sets the program counter to the address
 * specified in the address.
 *
 * This test checks the following:
 * - The program counter is set to the address
 **/
BOOST_DATA_TEST_CASE_F(Fixture, JUMPTests, JUMP_DATA, opcode, address){
    // Set the opcode
    interpreter.memory[0x200] = opcode;

    // Tick the interpreter
    interpreter.tick();

    // Check that the program counter is at the address
    BOOST_TEST(interpreter.registers.PC == address);
}

static auto EXE_opcode =       bdata::make({0x2329, 0x2FFF, 0x25CB, 0x2B14, 0x2118});
static auto EXE_address =      bdata::make({0x329,  0xFFF,  0x5CB,  0xB14,  0x118});
static auto EXE_Stack =        bdata::make({0x200,  0x190,  0x1C4,  0x1B7,  0x1DD});

// EXE Data
static auto EXE_DATA = EXE_opcode ^ EXE_address ^ EXE_Stack;

/**
 * EXE Instruction
 *
 * EXE instruction sets the program counter to the address
 * specified in the address.
 *
 * This test checks the following:
 * - The program counter is set to the address
 **/
BOOST_DATA_TEST_CASE_F(Fixture, EXETests, EXE_DATA, opcode, address, stackInitial){
    // Set the opcode
    interpreter.memory[0x200] = opcode;

    // Set the stack to the initial value
    interpreter.registers.SP = stackInitial;

    // Put the address in the stack
    interpreter.memory[interpreter.registers.SP+0] = (address & 0xFF00) >> 8;
    interpreter.memory[interpreter.registers.SP+1] = (address & 0x00FF) >> 0;

    // Tick the interpreter
    interpreter.tick();

    // Check that the program counter is at the address
    BOOST_TEST(interpreter.registers.PC == address);
    // Check that the stack pointer is incremented by 2
    BOOST_TEST(interpreter.registers.SP == stackInitial+2);
}

static auto BR_opcode =       bdata::make({0xB329, 0xBFFF, 0xB5CB, 0xBB14, 0xB118});
static auto BR_address =      bdata::make({0x329,  0xFFF,  0x5CB,  0xB14,  0x118});
static auto BR_Value =        bdata::make({0x0FF,  0x02C,  0x070,  0x0BB,  0x0A9});
static auto BR_Expected =     bdata::make({0x428,  0x02B,  0x63B,  0xBCF,  0x1C1});

// BR Data
static auto BR_DATA = BR_opcode ^ BR_address ^ BR_Value ^ BR_Expected;

/**
 * BR Instruction
 *
 * BR instruction sets the program counter to the specified
 * address plus the value of register V0.
 *
 * This test checks the following:
 * - The program counter is set to the address added with V0's value
 **/
BOOST_DATA_TEST_CASE_F(Fixture, BRTests, BR_DATA, opcode, address, value, expected){
    // Set the opcode
    interpreter.memory[0x200] = opcode;

    // Set register V0's value
    interpreter.registers.V[0] = value;

    // Tick the interpreter
    interpreter.tick();

    // Check that the program counter is at the address
    BOOST_TEST(interpreter.registers.PC == expected);
}

BOOST_AUTO_TEST_SUITE_END();
