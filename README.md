# ChipM8-Core
Chip8 Interpreter Core

## Dependencies
### Required
- CMake
### Optional
- Boost 1.66+

Note: Older versions of Boost may work, but 1.66+ has been tested to work

## Building
There are two build targets for CMake, the actual ChipM8 library and the unit tests. The library does not require Boost, but the unit tests do.


### Compiling libChipM8
1. Use CMake to generate the build file for your platform
2. Use the generated build file to compile the library 

### Compiling Unit Tests
The unit tests require the boost library, see Dependencies

1. Modify the INCLUDE_DIR variable within CMakeLists.txt to point at the Boost headers
2. Use CMake to generate the build file for your platform
3. Use the generated build file to compile the tests

## Usages
The main purpose of this library is to abstract out the graphics, input, and audio functionality of the interpreter.
I have created a simple SDL frontend for this library, however anyone is free to use this library to create their own Chip-8 frontend.

If you want to see my own frontend for this library, see my ChipM8-SDL repository.

[ChipM8-SDL](https://github.com/airloaf/ChipM8-SDL)