#include <boost/test/unit_test.hpp>

#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../../src/System/Interpreter.h"

// Alias namespace to bdata
namespace bdata = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(ProgramLoaderTests);

/**
 * Ensures the register starts with the correct
 * values.
 **/
BOOST_AUTO_TEST_CASE(TestProgramLoading){
    // Create an interpreter
    Interpreter interpreter;

    // Load the program in the data folder
    interpreter.loadProgram("../Data/TestLoader.ch8");

    // Test certain memory values
    BOOST_TEST(interpreter.memory[0x200] == 0x80);
    BOOST_TEST(interpreter.memory[0x204] == 0x12);
    BOOST_TEST(interpreter.memory[0x205] == 0x85);
    BOOST_TEST(interpreter.memory[0x208] == 0xE0);
    BOOST_TEST(interpreter.memory[0x209] == 0xE1);
    BOOST_TEST(interpreter.memory[0x20C] == 0xC1);
    BOOST_TEST(interpreter.memory[0x20F] == 0xD9);
    BOOST_TEST(interpreter.memory[0x210] == 0xC0);
    BOOST_TEST(interpreter.memory[0x214] == 0x23);
    BOOST_TEST(interpreter.memory[0x216] == 0x78);
}

BOOST_AUTO_TEST_SUITE_END();
