#include <boost/test/unit_test.hpp>

#include <Devices/MemoryMappedScreen.h>

BOOST_AUTO_TEST_SUITE(MemoryMappedScreenManipulation);

/**
 * This test checks that the constructor
 * properly sets the values in the meomry
 * mapped screen.
 **/
BOOST_AUTO_TEST_CASE(ConstructorTest){
    // Create an instance of the memory mapped screen
    MemoryMappedScreen screen;

    // Check each byte of the screen
    // Each byte should be 0
    // The screen consists of (64 X 32) pixels.
    // Each address contains 8 pixels so the
    // total amount of bytes is (64 * 32 / 8) =
    // 256.
    for(std::size_t screenAddress = 0; screenAddress < (64 * 32 / 8); screenAddress++){
        BOOST_TEST(screen.read(screenAddress) == 0);
    }
};

/**
 * This test case checks the trivial case of
 * writing to the screen when it is initially blank.
 *
 * The screen writes in XOR mode, but when the
 * screen is initially blank (All 0s), the value
 * written replaces the values in the screen.
 **/
BOOST_AUTO_TEST_CASE(ReadingAndWritingSimple){
    // Create an instance of the memory mapped screen
    MemoryMappedScreen screen;

    // Write to each (256) of the addresses.
    // The value written will simply be the
    // number corresponding to that address.
    for(std::size_t screenAddress = 0; screenAddress < (64 * 32 / 8); screenAddress++){
        screen.write(screenAddress, screenAddress);
    }

    // Read from each of the screen addresses to
    // see if they were set correctly
    for(std::size_t screenAddress = 0; screenAddress < (64 * 32 / 8); screenAddress++){
        BOOST_TEST(screen.read(screenAddress) == screenAddress);
    }
};

/**
 * The following tests are complicated cases
 * of writing to the screen. It's complicated
 * since we are writing to the screen with
 * some of the pixels already set.
 **/


/**
 * Complicated test 1
 *
 * Check that the following operation occurs successfully
 *
 *     01101101
 * XOR 11111111
 * ------------
 *     10010010
 **/
BOOST_AUTO_TEST_CASE(ReadingAndWritingComplicated1){
    // Create an instance of the memory mapped screen
    MemoryMappedScreen screen;

    // Write the value b01101101 == 109
    // to address 0
    screen.write(0, 109);

    // Check to ensure the value was 109
    BOOST_TEST(screen.read(0) == 109);

    // Write the value 0xFF == 255
    screen.write(0, 255);

    // Check to ensure the value was XOR'd
    // properly. The value should be 146
    BOOST_TEST(screen.read(0) == 146);
}

/**
 * Complicated test 2
 *
 * Check that the following operation occurs successfully
 *
 *     10011100
 * XOR 10011100
 * ------------
 *     00000000
 **/
BOOST_AUTO_TEST_CASE(ReadingAndWritingComplicated2){
    // Create an instance of the memory mapped screen
    MemoryMappedScreen screen;

    // Write the value 156
    // to address 0
    screen.write(0, 156);

    // Check to ensure the value was 156
    BOOST_TEST(screen.read(0) == 156);

    // Write the value 156
    screen.write(0, 156);

    // Check to ensure the value was XOR'd
    // properly. The value should be 0
    BOOST_TEST(screen.read(0) == 0);
}

BOOST_AUTO_TEST_SUITE_END();
