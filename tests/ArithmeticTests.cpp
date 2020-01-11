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
 * Arithmetic Tests
 *
 * Tests the following instructions
 * 
 * ADDI (7XNN)
 * COPY (8XY0)
 * OR   (8XY1)
 * AND  (8XY2)
 * XOR  (8XY3)
 * ADD  (8XY4)
 * SUB  (8XY5)
 * SHR  (8XY6)
 * SUBR (8XY7)
 * SHL  (8XYE)
 **/
BOOST_AUTO_TEST_SUITE(ArithmeticTests);

static auto ADDI_Opcode =           bdata::make({0x71FF, 0x7251, 0x7810, 0x7F44, 0x77C3});
static auto ADDI_RegisterNumber =   bdata::make({0x01, 0x02, 0x0B, 0x0F, 0x07});
static auto ADDI_RegisterValue =    bdata::make({0x00, 0xFF, 0xEF, 0x55, 0x3C});
static auto ADDI_Immediate =        bdata::make({0xFF, 0x51, 0x10, 0x44, 0xC3});
static auto ADDI_Expected =         bdata::make({0xFF, 0x50, 0xFF, 0x99, 0xFF});

// ADDI Data
static auto ADDI_DATA = ADDI_Opcode ^ ADDI_RegisterNumber ^ ADDI_RegisterValue ^ ADDI_Immediate ^ ADDI_Expected;

/**
 * ADDI Instruction Test
 *
 * This test checks the following:
 * - The register is set to the correct value
 **/
BOOST_DATA_TEST_CASE_F(Fixture, ADDITests, ADDI_DATA, opcode, registerNumber, registerInitialValue, immediateValue, expectedValue){
    // Set the opcode
    interpreter.memory[0x200] = opcode;

    // Set the initial register value
    interpreter.registers.V[registerNumber] = registerInitialValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the register has changed to the expected value
    BOOST_TEST(interpreter.registers.V[registerNumber] == expectedValue);
}

static auto COPY_Opcode =           bdata::make({0x81F0, 0x82C0, 0x8820, 0x8FE0, 0x8730});
static auto COPY_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0F, 0x07});
static auto COPY_RegisterY =        bdata::make({0x0F, 0x0C, 0x02, 0x0E, 0x03});
static auto COPY_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto COPY_RegisterYValue =   bdata::make({0x00, 0x49, 0x39, 0xE4, 0xCC});
static auto COPY_Expected =         bdata::make({0x00, 0x49, 0x39, 0xE4, 0xCC});


// COPY Data
static auto COPY_DATA = COPY_Opcode ^ COPY_RegisterX ^ COPY_RegisterY ^ COPY_RegisterXValue ^ COPY_RegisterYValue ^ COPY_Expected;

/**
 * COPY Instruction Test
 *
 * This test checks the following:
 * - RegisterX's value is equal to RegisterY's value
 **/
BOOST_DATA_TEST_CASE_F(Fixture, COPYTests, COPY_DATA, opcode, registerX, registerY, xValue, yValue, expected){
    // Set the opcode
    interpreter.memory[0x200] = opcode;

    // Set the initial register values
    interpreter.registers.V[registerX] = xValue;
    interpreter.registers.V[registerY] = yValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the register has changed to the expected value
    BOOST_TEST(interpreter.registers.V[registerX] == expected);
}

static auto OR_Opcode =           bdata::make({0x81F1, 0x82C1, 0x8821, 0x8FE1, 0x8731});
static auto OR_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0F, 0x07});
static auto OR_RegisterY =        bdata::make({0x0F, 0x0C, 0x02, 0x0E, 0x03});
static auto OR_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto OR_RegisterYValue =   bdata::make({0x00, 0x49, 0x39, 0xE4, 0xCC});
static auto OR_Expected =         bdata::make({0x23, 0xFF, 0x39, 0xF6, 0xDD});


// OR Data
static auto OR_DATA = OR_Opcode ^ OR_RegisterX ^ OR_RegisterY ^ OR_RegisterXValue ^ OR_RegisterYValue ^ OR_Expected;

/**
 * OR Instruction Test
 *
 * This test checks the following:
 * - RegisterX's value is equal to the x-value OR'd with the y-value
 **/
BOOST_DATA_TEST_CASE_F(Fixture, ORTests, OR_DATA, opcode, registerX, registerY, xValue, yValue, expected){
    // Set the opcode
    interpreter.memory[0x200] = opcode;

    // Set the initial register values
    interpreter.registers.V[registerX] = xValue;
    interpreter.registers.V[registerY] = yValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the register has changed to the expected value
    BOOST_TEST(interpreter.registers.V[registerX] == expected);
}

static auto AND_Opcode =           bdata::make({0x81F2, 0x82C2, 0x8822, 0x8FE2, 0x8732});
static auto AND_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0F, 0x07});
static auto AND_RegisterY =        bdata::make({0x0F, 0x0C, 0x02, 0x0E, 0x03});
static auto AND_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto AND_RegisterYValue =   bdata::make({0x00, 0x49, 0x39, 0xE4, 0xCC});
static auto AND_Expected =         bdata::make({0x00, 0x49, 0x00, 0xE0, 0x48});


// AND Data
static auto AND_DATA = AND_Opcode ^ AND_RegisterX ^ AND_RegisterY ^ AND_RegisterXValue ^ AND_RegisterYValue ^ AND_Expected;

/**
 * AND Instruction Test
 *
 * This test checks the following:
 * - RegisterX's value is equal to the x-value AND'd with the y-value
 **/
BOOST_DATA_TEST_CASE_F(Fixture, ANDTests, AND_DATA, opcode, registerX, registerY, xValue, yValue, expected){
    // Set the opcode
    interpreter.memory[0x200] = opcode;

    // Set the initial register values
    interpreter.registers.V[registerX] = xValue;
    interpreter.registers.V[registerY] = yValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the register has changed to the expected value
    BOOST_TEST(interpreter.registers.V[registerX] == expected);
}

static auto XOR_Opcode =           bdata::make({0x81F3, 0x82C3, 0x8823, 0x8FE3, 0x8733});
static auto XOR_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0F, 0x07});
static auto XOR_RegisterY =        bdata::make({0x0F, 0x0C, 0x02, 0x0E, 0x03});
static auto XOR_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto XOR_RegisterYValue =   bdata::make({0x00, 0x49, 0x39, 0xE4, 0xCC});
static auto XOR_Expected =         bdata::make({0x23, 0xB6, 0x39, 0x16, 0x95});

// XOR Data
static auto XOR_DATA = XOR_Opcode ^ XOR_RegisterX ^ XOR_RegisterY ^ XOR_RegisterXValue ^ XOR_RegisterYValue ^ XOR_Expected;

/**
 * XOR Instruction Test
 *
 * This test checks the following:
 * - RegisterX's value is equal to the x-value XOR'd with the y-value
 **/
BOOST_DATA_TEST_CASE_F(Fixture, XORTests, XOR_DATA, opcode, registerX, registerY, xValue, yValue, expected){
    // Set the opcode
    interpreter.memory[0x200] = opcode;

    // Set the initial register values
    interpreter.registers.V[registerX] = xValue;
    interpreter.registers.V[registerY] = yValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the register has changed to the expected value
    BOOST_TEST(interpreter.registers.V[registerX] == expected);
}

static auto ADD_Opcode =           bdata::make({0x81E4, 0x82C4, 0x8824, 0x8CE4, 0x8734});
static auto ADD_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0C, 0x07});
static auto ADD_RegisterY =        bdata::make({0x0E, 0x0C, 0x02, 0x0E, 0x03});
static auto ADD_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto ADD_RegisterYValue =   bdata::make({0x00, 0x49, 0x39, 0xE4, 0xCC});
static auto ADD_Expected =         bdata::make({0x23, 0x48, 0x39, 0xD6, 0x25});
static auto ADD_Flag =             bdata::make({0x00, 0x01, 0x00, 0x01, 0x01});

// ADD Data
static auto ADD_DATA = ADD_Opcode ^ ADD_RegisterX ^ ADD_RegisterY ^ ADD_RegisterXValue ^ ADD_RegisterYValue ^ ADD_Expected ^ ADD_Flag;

/**
 * ADD Instruction Test
 *
 * This test checks the following:
 * - RegisterX's value is equal to the x-value ADD'd with the y-value
 * - RegisterF's value is set to 1 on overflow, 0 otherwise
 **/
BOOST_DATA_TEST_CASE_F(Fixture, ADDTests, ADD_DATA, opcode, registerX, registerY, xValue, yValue, expected, flag){
    // Set the opcode
    interpreter.memory[0x200] = opcode;

    // Set the initial register values
    interpreter.registers.V[registerX] = xValue;
    interpreter.registers.V[registerY] = yValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the register has changed to the expected value
    BOOST_TEST(interpreter.registers.V[registerX] == expected);

    // Check that the flag is set to the proper value
    BOOST_TEST(interpreter.registers.V[0xF] == flag);
}

static auto SUB_Opcode =           bdata::make({0x81E5, 0x82C5, 0x8825, 0x8CE5, 0x8735});
static auto SUB_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0C, 0x07});
static auto SUB_RegisterY =        bdata::make({0x0E, 0x0C, 0x02, 0x0E, 0x03});
static auto SUB_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto SUB_RegisterYValue =   bdata::make({0x00, 0x49, 0x39, 0xE4, 0xCC});
static auto SUB_Expected =         bdata::make({0x23, 0xB6, 0xC7, 0x0E, 0x8D});
static auto SUB_Flag =             bdata::make({0x00, 0x00, 0x01, 0x00, 0x01});

// SUB Data
static auto SUB_DATA = SUB_Opcode ^ SUB_RegisterX ^ SUB_RegisterY ^ SUB_RegisterXValue ^ SUB_RegisterYValue ^ SUB_Expected ^ SUB_Flag;

/**
 * SUB Instruction Test
 *
 * This test checks the following:
 * - RegisterX's value is equal to the x-value SUB'd with the y-value
 * - RegisterF's value is set to 1 on overflow, 0 otherwise
 **/
BOOST_DATA_TEST_CASE_F(Fixture, SUBTests, SUB_DATA, opcode, registerX, registerY, xValue, yValue, expected, flag){
    // Set the opcode
    interpreter.memory[0x200] = opcode;

    // Set the initial register values
    interpreter.registers.V[registerX] = xValue;
    interpreter.registers.V[registerY] = yValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the register has changed to the expected value
    BOOST_TEST(interpreter.registers.V[registerX] == expected);

    // Check that the flag is set to the proper value
    BOOST_TEST(interpreter.registers.V[0xF] == flag);
}

static auto SHR_Opcode =           bdata::make({0x81E6, 0x82C6, 0x8826, 0x8CE6, 0x8736});
static auto SHR_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0C, 0x07});
static auto SHR_RegisterY =        bdata::make({0x0E, 0x0C, 0x02, 0x0E, 0x03});
static auto SHR_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto SHR_RegisterYValue =   bdata::make({0x00, 0x49, 0x39, 0xE4, 0xCC});
static auto SHR_Expected =         bdata::make({0x00, 0x26, 0x1C, 0x82, 0x66});
static auto SHR_Flag =             bdata::make({0x00, 0x01, 0x01, 0x00, 0x00});

// SHR Data
static auto SHR_DATA = SHR_Opcode ^ SHR_RegisterX ^ SHR_RegisterY ^ SHR_RegisterXValue ^ SHR_RegisterYValue ^ SHR_Expected ^ SHR_Flag;

/**
 * SHR Instruction Test
 *
 * This test checks the following:
 * - RegisterX's value is equal to the x-value SHR'd with the y-value
 * - RegisterF's value is set to 1 on overflow, 0 otherwise
 **/
BOOST_DATA_TEST_CASE_F(Fixture, SHRTests, SHR_DATA, opcode, registerX, registerY, xValue, yValue, expected, flag){
    // Set the opcode
    interpreter.memory[0x200] = opcode;

    // Set the initial register values
    interpreter.registers.V[registerX] = xValue;
    interpreter.registers.V[registerY] = yValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the register has changed to the expected value
    BOOST_TEST(interpreter.registers.V[registerX] == expected);

    // Check that the flag is set to the proper value
    BOOST_TEST(interpreter.registers.V[0xF] == flag);
}

static auto SUBR_Opcode =           bdata::make({0x81E7, 0x82C7, 0x8827, 0x8CE7, 0x8737});
static auto SUBR_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0C, 0x07});
static auto SUBR_RegisterY =        bdata::make({0x0E, 0x0C, 0x02, 0x0E, 0x03});
static auto SUBR_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto SUBR_RegisterYValue =   bdata::make({0x00, 0x49, 0x39, 0xE4, 0xCC});
static auto SUBR_Expected =         bdata::make({0xDD, 0x4A, 0x39, 0xF2, 0x73});
static auto SUBR_Flag =             bdata::make({0x01, 0x01, 0x00, 0x01, 0x00});

// SUBR Data
static auto SUBR_DATA = SUBR_Opcode ^ SUBR_RegisterX ^ SUBR_RegisterY ^ SUBR_RegisterXValue ^ SUBR_RegisterYValue ^ SUBR_Expected ^ SUBR_Flag;

/**
 * SUBR Instruction Test
 *
 * This test checks the following:
 * - RegisterX's value is equal to the x-value SUBR'd with the y-value
 * - RegisterF's value is set to 1 on overflow, 0 otherwise
 **/
BOOST_DATA_TEST_CASE_F(Fixture, SUBRTests, SUBR_DATA, opcode, registerX, registerY, xValue, yValue, expected, flag){
    // Set the opcode
    interpreter.memory[0x200] = opcode;

    // Set the initial register values
    interpreter.registers.V[registerX] = xValue;
    interpreter.registers.V[registerY] = yValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the register has changed to the expected value
    BOOST_TEST(interpreter.registers.V[registerX] == expected);

    // Check that the flag is set to the proper value
    BOOST_TEST(interpreter.registers.V[0xF] == flag);
}

static auto SHL_Opcode =           bdata::make({0x81EE, 0x82CE, 0x882E, 0x8CEE, 0x873E});
static auto SHL_RegisterX =        bdata::make({0x01, 0x02, 0x0B, 0x0C, 0x07});
static auto SHL_RegisterY =        bdata::make({0x0E, 0x0C, 0x02, 0x0E, 0x03});
static auto SHL_RegisterXValue =   bdata::make({0x23, 0xFF, 0x00, 0xF2, 0x59});
static auto SHL_RegisterYValue =   bdata::make({0x00, 0x49, 0x39, 0xE4, 0xCC});
static auto SHL_Expected =         bdata::make({0x00, 0x92, 0x72, 0xC8, 0x98});
static auto SHL_Flag =             bdata::make({0x00, 0x00, 0x00, 0x01, 0x01});

// SHL Data
static auto SHL_DATA = SHL_Opcode ^ SHL_RegisterX ^ SHL_RegisterY ^ SHL_RegisterXValue ^ SHL_RegisterYValue ^ SHL_Expected ^ SHL_Flag;

/**
 * SHL Instruction Test
 *
 * This test checks the following:
 * - RegisterX's value is equal to the x-value SHL'd with the y-value
 * - RegisterF's value is set to 1 on overflow, 0 otherwise
 **/
BOOST_DATA_TEST_CASE_F(Fixture, SHLTests, SHL_DATA, opcode, registerX, registerY, xValue, yValue, expected, flag){
    // Set the opcode
    interpreter.memory[0x200] = opcode;

    // Set the initial register values
    interpreter.registers.V[registerX] = xValue;
    interpreter.registers.V[registerY] = yValue;

    // Tick the interpreter
    interpreter.tick();

    // Check that the register has changed to the expected value
    BOOST_TEST(interpreter.registers.V[registerX] == expected);

    // Check that the flag is set to the proper value
    BOOST_TEST(interpreter.registers.V[0xF] == flag);
}

BOOST_AUTO_TEST_SUITE_END();
