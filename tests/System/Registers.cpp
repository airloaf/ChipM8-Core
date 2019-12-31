#include <boost/test/unit_test.hpp>

#include <System/Registers.h>

#include <stdexcept>
#include <stddef.h>

BOOST_AUTO_TEST_SUITE(RegisterTests);

/**
 * This test checks that we are able to
 * write to each of the 16 general
 * purpose registers without issue.
 **/
BOOST_AUTO_TEST_CASE(WriteToValidVRegisters){
    // Create a registers object
    Registers registers;

    // Iterate through each of the 16 general purpose registers
    for(std::size_t registerNumber = 0; registerNumber < 16; registerNumber++){
        // Write to the 16 registers. Using random value 100
        BOOST_CHECK_NO_THROW(registers.setVRegister(registerNumber, 100));
    }
}

/**
 * This test checks that writing to invalid
 * general purpose registers results in a
 * domain error being thrown.
 **/
BOOST_AUTO_TEST_CASE(WriteToInvalidVRegisters){
    // Create a registers object
    Registers registers;

    // Check that an exception is thrown for size_t values > 15
    for(std::size_t registerNumber = 16; registerNumber < SIZE_MAX; registerNumber++){
        // Write to the register using random value 100
        BOOST_CHECK_THROW(registers.setVRegister(registerNumber, 100), std::domain_error);
    }
}

/**
 * This test checks that we can read from valid
 * general purpose registers. (0-15)
 **/
BOOST_AUTO_TEST_CASE(ReadingFromValidVRegisters){
    // Create a registers object
    Registers registers;

    // Iterate through each of the 16 general purpose registers
    for(std::size_t registerNumber = 0; registerNumber < 16; registerNumber++){
        // Write to the 16 registers. Using random value 100
        registers.setVRegister(registerNumber, 100);
    }

    // Iterate through each of the 16 general purpose registers
    for(std::size_t registerNumber = 0; registerNumber < 16; registerNumber++){
        // Read from the 16 registers. 
        BOOST_TEST(registers.getVRegister(registerNumber) == 100);
    }
}

/**
 * This test checks that we can't read from invalid
 * general purpose registers.
 **/
BOOST_AUTO_TEST_CASE(ReadingFromInvalidVRegisters){
    // Create a registers object
    Registers registers;

    // Check that an exception is thrown for size_t values > 15
    for(std::size_t registerNumber = 16; registerNumber < SIZE_MAX; registerNumber++){
        // read from the register
        BOOST_CHECK_THROW(registers.getVRegister(registerNumber), std::domain_error);
    }
}

BOOST_AUTO_TEST_SUITE_END()
