#include <boost/test/unit_test.hpp>

#include <Devices/MemoryMappedInput.h>

BOOST_AUTO_TEST_SUITE(MemoryMappedInputManipulation);

/**
 * This test checks that the constructor
 * properly sets the values in the memory
 * mapped input
 **/
BOOST_AUTO_TEST_CASE(ConstructorTest){
    // Create an instance of the memory mapped input
    MemoryMappedInput input;

    // Check each byte of the input
    BOOST_TEST(input.read(0) == 0);
    BOOST_TEST(input.read(1) == 0);
}

/**
 * This test checks that the memory
 * mapped input can be wrote to
 * correctly.
 **/
BOOST_AUTO_TEST_CASE(SettingKeysPressed){
    // Create and instance of the memory mapped input
    MemoryMappedInput input;

    // Write all keys pressed to all 16 keys
    input.write(0, 0xFF);
    input.write(1, 0xFF);

    // Check that the input has all the keys pressed
    BOOST_TEST(input.read(0) == 0xFF);
    BOOST_TEST(input.read(1) == 0xFF);
}

BOOST_AUTO_TEST_SUITE_END();
