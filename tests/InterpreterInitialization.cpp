#include <boost/test/unit_test.hpp>

#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/System/Interpreter.h"

// Alias namespace to bdata
namespace bdata = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(InitializationTests);

/**
 * Ensures the register starts with the correct
 * values.
 **/
BOOST_AUTO_TEST_CASE(TestRegisterInitialValues){
    // Create an interpreter
    Interpreter interpreter;

    // All general purpose registers should be set to 0
    for(std::size_t registerNumber = 0; registerNumber < 16; registerNumber++){
        BOOST_TEST(interpreter.registers.V[registerNumber] == 0);
    }

    // Stack pointer and program counter should be set to 0x200
    BOOST_TEST(interpreter.registers.PC == 0x200);
    BOOST_TEST(interpreter.registers.SP == 0x200);

    // The sound and delay timers should be 0
    BOOST_TEST(interpreter.registers.ST == 0);
    BOOST_TEST(interpreter.registers.DT == 0);
}

/**
 * Checks that the 0 hex digit is properly set in memory
 **/
BOOST_AUTO_TEST_CASE(HexDigits0){
    // Create an interpreter
    Interpreter interpreter;

    uint16_t addressOffset = 0x00;

    // Check that 0 is stored in memory properly
    BOOST_TEST(interpreter.memory[0x00 + addressOffset] == 0xF0);
    BOOST_TEST(interpreter.memory[0x01 + addressOffset] == 0x90);
    BOOST_TEST(interpreter.memory[0x02 + addressOffset] == 0x90);
    BOOST_TEST(interpreter.memory[0x03 + addressOffset] == 0x90);
    BOOST_TEST(interpreter.memory[0x04 + addressOffset] == 0xF0);
}

/**
 * Checks that the 1 hex digit is properly set in memory
 **/
BOOST_AUTO_TEST_CASE(HexDigits1){
    // Create an interpreter
    Interpreter interpreter;

    uint16_t addressOffset = 0x05;

    // Check that 0 is stored in memory properly
    BOOST_TEST(interpreter.memory[0x00 + addressOffset] == 0x20);
    BOOST_TEST(interpreter.memory[0x01 + addressOffset] == 0x60);
    BOOST_TEST(interpreter.memory[0x02 + addressOffset] == 0x20);
    BOOST_TEST(interpreter.memory[0x03 + addressOffset] == 0x20);
    BOOST_TEST(interpreter.memory[0x04 + addressOffset] == 0x70);
}

/**
 * Checks that the 2 hex digit is properly set in memory
 **/
BOOST_AUTO_TEST_CASE(HexDigits2){
    // Create an interpreter
    Interpreter interpreter;

    uint16_t addressOffset = 0x0A;

    // Check that 0 is stored in memory properly
    BOOST_TEST(interpreter.memory[0x00 + addressOffset] == 0xF0);
    BOOST_TEST(interpreter.memory[0x01 + addressOffset] == 0x10);
    BOOST_TEST(interpreter.memory[0x02 + addressOffset] == 0xF0);
    BOOST_TEST(interpreter.memory[0x03 + addressOffset] == 0x80);
    BOOST_TEST(interpreter.memory[0x04 + addressOffset] == 0xF0);
}

/**
 * Checks that the 3 hex digit is properly set in memory
 **/
BOOST_AUTO_TEST_CASE(HexDigits3){
    // Create an interpreter
    Interpreter interpreter;

    uint16_t addressOffset = 0x0F;

    // Check that 0 is stored in memory properly
    BOOST_TEST(interpreter.memory[0x00 + addressOffset] == 0xF0);
    BOOST_TEST(interpreter.memory[0x01 + addressOffset] == 0x10);
    BOOST_TEST(interpreter.memory[0x02 + addressOffset] == 0xF0);
    BOOST_TEST(interpreter.memory[0x03 + addressOffset] == 0x10);
    BOOST_TEST(interpreter.memory[0x04 + addressOffset] == 0xF0);
}

/**
 * Checks that the 4 hex digit is properly set in memory
 **/
BOOST_AUTO_TEST_CASE(HexDigits4){
    // Create an interpreter
    Interpreter interpreter;

    uint16_t addressOffset = 0x14;

    // Check that 0 is stored in memory properly
    BOOST_TEST(interpreter.memory[0x00 + addressOffset] == 0x90);
    BOOST_TEST(interpreter.memory[0x01 + addressOffset] == 0x90);
    BOOST_TEST(interpreter.memory[0x02 + addressOffset] == 0xF0);
    BOOST_TEST(interpreter.memory[0x03 + addressOffset] == 0x10);
    BOOST_TEST(interpreter.memory[0x04 + addressOffset] == 0x10);
}

/**
 * Checks that the 5 hex digit is properly set in memory
 **/
BOOST_AUTO_TEST_CASE(HexDigits5){
    // Create an interpreter
    Interpreter interpreter;

    uint16_t addressOffset = 0x19;

    // Check that 0 is stored in memory properly
    BOOST_TEST(interpreter.memory[0x00 + addressOffset] == 0xF0);
    BOOST_TEST(interpreter.memory[0x01 + addressOffset] == 0x80);
    BOOST_TEST(interpreter.memory[0x02 + addressOffset] == 0xF0);
    BOOST_TEST(interpreter.memory[0x03 + addressOffset] == 0x10);
    BOOST_TEST(interpreter.memory[0x04 + addressOffset] == 0xF0);
}

/**
 * Checks that the 6 hex digit is properly set in memory
 **/
BOOST_AUTO_TEST_CASE(HexDigits6){
    // Create an interpreter
    Interpreter interpreter;

    uint16_t addressOffset = 0x1E;

    // Check that 0 is stored in memory properly
    BOOST_TEST(interpreter.memory[0x00 + addressOffset] == 0xF0);
    BOOST_TEST(interpreter.memory[0x01 + addressOffset] == 0x80);
    BOOST_TEST(interpreter.memory[0x02 + addressOffset] == 0xF0);
    BOOST_TEST(interpreter.memory[0x03 + addressOffset] == 0x90);
    BOOST_TEST(interpreter.memory[0x04 + addressOffset] == 0xF0);
}

BOOST_AUTO_TEST_SUITE_END();
