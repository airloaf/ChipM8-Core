#include <boost/test/unit_test.hpp>
#include <Bus/Bus.h>
#include <Devices/Memory.h>


BOOST_AUTO_TEST_SUITE(RegisteringMemory)

/**
* This test checks that the memory
* can be read in the range it was
* registered on the bus. The memory
* device is registered to all
* addressable ranges.
**/
BOOST_AUTO_TEST_CASE(RegisterMemory1){
    
    // Allocate a bus with 4KB of memory
    Bus bus(4096);

    // Allocate memory with 4KB of memory
    Memory mem(4096);

    // Register the memory to the entire addressable range
    bus.registerReadableDevice((ReadableDevice *) &mem, 0, 4096);

    // Write to memory at address 0
    mem.write(0, 200);

    // Read address 0 from the bus
    BOOST_TEST(bus.read(0) == 200);

    // Write to memory at address 4095
    mem.write(4095, 150);

    // Read address 4095 from the bus
    BOOST_TEST(bus.read(4095) == 150);
}

/**
* This test checks that the memory
* can be read in the range it was
* registered on the bus. The memory
* device is registered to the lower
* half of the addressable range of
* the bus.
**/
BOOST_AUTO_TEST_CASE(RegisterMemory2){
    // Allocate a bus with 4KB of memory
    Bus bus(4096);

    // Allocate memory with 2KB of memory
    Memory mem(2048);

    // Register the memory to the lower half of the bus
    bus.registerReadableDevice((ReadableDevice *) &mem, 0, 2048);

    // Write to memory at address 0
    mem.write(0, 250);

    // Read address 0 from the bus
    BOOST_TEST(bus.read(0) == 250);
    
    // Write to the memory at address 2047
    mem.write(2047, 149);

    // Read address 2047 from the bus
    BOOST_TEST(bus.read(2047) == 149);

    for(std::size_t address = 2048; address < 4096; address++){
        BOOST_CHECK_THROW(bus.read(address), std::out_of_range);
    }
}

/**
* This test checks that the memory
* can be read in the range it was
* registered on the bus. The memory
* device is registered to the upper
* half of the addressable range of
* the bus.
**/
BOOST_AUTO_TEST_CASE(RegisterMemory3){
    // Allocate a bus with 4KB of memory
    Bus bus(4096);

    // Allocate memory with 2KB of memory
    Memory mem(2048);

    // Register the memory to the upper half of the bus.
    bus.registerReadableDevice((ReadableDevice *) &mem, 2048, 4096);

    // Write to memory at address 0
    mem.write(0, 250);

    // Read address 2048 from the bus
    BOOST_TEST(bus.read(2048) == 250);
    
    // Write to the memory at address 2047
    mem.write(2047, 149);

    // Read address 4095 from the bus
    BOOST_TEST(bus.read(4095) == 149);

    // Check that the addresses from 0 to 2048 are invalid
    for(std::size_t address = 0; address < 2048; address++){
        BOOST_CHECK_THROW(bus.read(address), std::out_of_range);
    }
}

/**
 * This test checks that multiple memory
 * devices can be registered to the bus
 * and addressable separately.
**/
BOOST_AUTO_TEST_CASE(RegisterMemory4){
    // Allocate a bus with 4KB of memory
    Bus bus(4096);

    // Allocate memory with 2KB of memory
    // for the lower half of the bus.
    Memory lowerMem(2048);

    // Allocate memory with 2KB of memory
    // for the upper half of the bus.
    Memory upperMem(2048);

    // Register the memory to the lower half of the bus.
    bus.registerReadableDevice((ReadableDevice *) &lowerMem, 0, 2048);
    // Register the memory to the upper half of the bus.
    bus.registerReadableDevice((ReadableDevice *) &upperMem, 2048, 4096);

    // Write to the lower memory at address 0
    lowerMem.write(0, 250);

    // Read address 0 from the bus
    BOOST_TEST(bus.read(0) == 250);
    
    // Write to the lower memory at address 2047
    lowerMem.write(2047, 149);

    // Read address 2047 from the bus
    BOOST_TEST(bus.read(2047) == 149);

    // Write to the upper memory at address 0
    upperMem.write(0, 250);

    // Read address 2048 from the bus
    BOOST_TEST(bus.read(2048) == 250);
    
    // Write to the upper memory at address 2047
    upperMem.write(2047, 149);

    // Read address 4095 from the bus
    BOOST_TEST(bus.read(4095) == 149);
}

BOOST_AUTO_TEST_SUITE_END()
