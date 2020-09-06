cmake_minimum_required(VERSION 3.9)

# The type of library, STATIC or SHARED
set(LIB_TYPE SHARED)

# Development Library Paths
set(INCLUDE_DIR C:/DevelopmentLibraries/include/)
set(LIB_DIR C:/DevelopmentLibraries/lib/x64/)

project(ChipM8_Project)

###########################################################################
# Library
###########################################################################

# Find all source files
file(GLOB_RECURSE LIB_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)

# Create the library
add_library(ChipM8 ${LIB_TYPE} ${LIB_SRCS})

# Include the library headers
target_include_directories(ChipM8 PUBLIC include)

###########################################################################
# Tests
###########################################################################

# Find all test files
file(GLOB_RECURSE TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} tests/*.cpp)

# Create an executable for testing
add_executable(Tests ${TEST_SRCS})
target_link_libraries(Tests ChipM8)

# Link the include directory and Boost headers
target_include_directories(Tests PUBLIC include)
target_include_directories(Tests PUBLIC ${INCLUDE_DIR})