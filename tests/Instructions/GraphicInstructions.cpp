#include <boost/test/unit_test.hpp>

#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <ChipM8/System/Interpreter.h>

#include <vector>

// Alias namespace to bdata
namespace bdata = boost::unit_test::data;


/**
 * Screen with pixels values equal
 * to their byte values for each
 * group of 8 pixels.
 **/
struct AssortedScreen{
    void setup(){
        for(std::size_t row = 0; row < 32; row++){
            for(std::size_t col = 0; col < 8; col++){
                for(std::size_t pixel = 0; pixel < 8; pixel++){
                    int value = col*8 + pixel;
                    bool lit = (value & (1 << pixel));
                    interpreter.screen.setPixel(row, col, lit);
                }
            }
        }
    }

    Interpreter interpreter;
};

/**
 * Blank Screen Fixture
 **/
struct BlankScreen{

    Interpreter interpreter;

};

/**
 * Screen with all pixels set to
 * lit
 **/
struct FilledScreen{
    void setup(){
        for(std::size_t row = 0; row < 32; row++){
            for(std::size_t col = 0; col < 64; col++){
                interpreter.screen.setPixel(row, col, true);
            }
        }
    }
    Interpreter interpreter;
};

/**
 * Input Tests
 *
 * Tests the following instructions
 * Each of them involve usage of the input
 * object
 *
 * CLS  (00E0)
 * DRAW (DXYN)
 **/
BOOST_AUTO_TEST_SUITE(InputTests);

/**
 * CLS Instruction Test
 *
 * Sets all the pixels on the screen to off
 *
 * This test checks the following:
 * - The pixels in the screen are set to off (0).
 *
 **/
BOOST_FIXTURE_TEST_CASE(CLSTest1, AssortedScreen){
    uint16_t opcode = 0x00E0;
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    // Tick the interpreter
    interpreter.tick();

    // Check each pixel is set 
    for(std::size_t row = 0; row < 32; row++){
        for(std::size_t col = 0; col < 64; col++){
            BOOST_TEST(!interpreter.screen.getPixel(row, col));
        }
    }

}

/**
 * DRAW Instruction Test Simple
 *
 * Draws the number 1 at location (7, 9)
 * on a blank screen.
 *
 * This test checks the following:
 * - The pixels are properly set starting at (7, 9)
 *
 **/
BOOST_FIXTURE_TEST_CASE(DRAWTestSimple, BlankScreen){
    uint16_t opcode = 0xD015;
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    interpreter.registers.V[0] = 7;
    interpreter.registers.V[1] = 9;

    interpreter.registers.I = 0x5;

    // Tick the interpreter
    interpreter.tick();

    // Check that the correct pixels are on
    BOOST_TEST(interpreter.screen.getPixel(7 + 0, 9 + 2));
    BOOST_TEST(interpreter.screen.getPixel(7 + 1, 9 + 1));
    BOOST_TEST(interpreter.screen.getPixel(7 + 1, 9 + 2));
    BOOST_TEST(interpreter.screen.getPixel(7 + 2, 9 + 2));
    BOOST_TEST(interpreter.screen.getPixel(7 + 3, 9 + 2));
    BOOST_TEST(interpreter.screen.getPixel(7 + 4, 9 + 1));
    BOOST_TEST(interpreter.screen.getPixel(7 + 4, 9 + 2));
    BOOST_TEST(interpreter.screen.getPixel(7 + 4, 9 + 3));
}

/**
 * DRAW Instruction Test Simple 2
 *
 * Draws the number 0 at location (20, 1)
 * on a Filled Screen
 *
 * This test checks the following:
 * - The pixels are properly set starting at (20, 1)
 *
 **/
BOOST_FIXTURE_TEST_CASE(DRAWTestSimple2, FilledScreen){
    uint16_t opcode = 0xD015;
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    interpreter.registers.V[0] = 20;
    interpreter.registers.V[1] = 1;

    interpreter.registers.I = 0x0;

    // Tick the interpreter
    interpreter.tick();

    // Check that the correct pixels are on
    BOOST_TEST(interpreter.screen.getPixel(20 + 1, 1 + 1));
    BOOST_TEST(interpreter.screen.getPixel(20 + 1, 1 + 2));
    BOOST_TEST(interpreter.screen.getPixel(20 + 2, 1 + 1));
    BOOST_TEST(interpreter.screen.getPixel(20 + 2, 1 + 2));
    BOOST_TEST(interpreter.screen.getPixel(20 + 3, 1 + 1));
    BOOST_TEST(interpreter.screen.getPixel(20 + 3, 1 + 2));

    for(int row = 0; row < 5; row++){
        for(int col = 0; col < 4; col++){
            BOOST_TEST(interpreter.screen.getPixel(20 + row, col + 5));
        }
    }
}

/**
 * DRAW Instruction Test Simple 3
 *
 * Draws the number 7 at location (30, 62)
 * on a Blank Screen
 *
 * This test checks the following:
 * - The pixels are properly set starting at (30, 62)
 *
 **/
BOOST_FIXTURE_TEST_CASE(DRAWTestSimple3, BlankScreen){
    uint16_t opcode = 0xD015;
    // Set the opcode
    interpreter.memory[0x200] = (opcode & 0xFF00) >> 8;
    interpreter.memory[0x201] = (opcode & 0x00FF) >> 0;

    interpreter.registers.V[0] = 30;
    interpreter.registers.V[1] = 62;

    interpreter.registers.I = 0x23;

    // Tick the interpreter
    interpreter.tick();

    // Check that the correct pixels are on
    BOOST_TEST(interpreter.screen.getPixel(30, 62));
    BOOST_TEST(interpreter.screen.getPixel(30, 63));
    BOOST_TEST(!interpreter.screen.getPixel(31, 62));
    BOOST_TEST(!interpreter.screen.getPixel(31, 63));

    BOOST_TEST(!interpreter.screen.getPixel(00, 62));
    BOOST_TEST(!interpreter.screen.getPixel(00, 63));
    BOOST_TEST(!interpreter.screen.getPixel(01, 62));
    BOOST_TEST(interpreter.screen.getPixel(01, 63));
    BOOST_TEST(!interpreter.screen.getPixel(02, 62));
    BOOST_TEST(interpreter.screen.getPixel(02, 63));

    BOOST_TEST(interpreter.screen.getPixel(30, 00));
    BOOST_TEST(interpreter.screen.getPixel(30, 01));
    BOOST_TEST(!interpreter.screen.getPixel(31, 00));
    BOOST_TEST(interpreter.screen.getPixel(31, 01));

    BOOST_TEST(interpreter.screen.getPixel(00, 00));
    BOOST_TEST(!interpreter.screen.getPixel(00, 01));
    BOOST_TEST(!interpreter.screen.getPixel(01, 00));
    BOOST_TEST(!interpreter.screen.getPixel(01, 01));
    BOOST_TEST(!interpreter.screen.getPixel(02, 00));
    BOOST_TEST(!interpreter.screen.getPixel(02, 01));
}

BOOST_AUTO_TEST_SUITE_END();
