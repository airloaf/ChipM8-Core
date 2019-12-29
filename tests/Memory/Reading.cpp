#include <boost/test/unit_test.hpp>

#include <Devices/Memory.h>

BOOST_AUTO_TEST_SUITE(ReadingTests)

BOOST_AUTO_TEST_CASE(ReadInRange){
    // Allocate 4KB of memory
    Memory mem(4096);

    // Write 0 to address 0
    mem.write(0, 0);

    // Check if the value was 0
    BOOST_TEST(mem.read(0) == 0);

    // Write 10 to address 0
    mem.write(0, 10);

    // Check if the value was 10
    BOOST_TEST(mem.read(0) == 10);
}

BOOST_AUTO_TEST_CASE(ReadInRange2){
    // Allocate 4KB of memory
    Memory mem(4096);

    // Write 100 to address 4095
    mem.write(4095, 100);

    // Check if the value was 100
    BOOST_TEST(mem.read(4095) == 100);
}

BOOST_AUTO_TEST_CASE(ReadOutOfRange){
    // Allocate 4KB of memory
    Memory mem(4096);

    // Read from address 4096
    BOOST_CHECK_THROW(mem.read(4096), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
