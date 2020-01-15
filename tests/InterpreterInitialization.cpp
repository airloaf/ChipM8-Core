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

static auto HexDigitValues = bdata::make({
        0xF0, 0xF0 
        });

/**
 * Checks that the Hexadecimal Digtis are set up correctly in memory.
 **/
BOOST_AUTO_TEST_CASE(HexDigits){
    // Create an interpreter
    Interpreter interpreter;

}

BOOST_AUTO_TEST_SUITE_END();
