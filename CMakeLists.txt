cmake_minimum_required(VERSION 3.9)

# The type of library, STATIC or SHARED
set(LIB_TYPE STATIC)

# Development Library Paths
set(INCLUDE_DIR C:/DevelopmentLibraries/include/)

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

###########################################################################
# Doxygen
###########################################################################
# Look for package, Doxygen
find_package(Doxygen)
# If we have doxygen installed, generate documentation
if(DOXYGEN_FOUND)
    # Set the input and cmake doxygen files
    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYFILE_CMAKE ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile_cmake)

    # Make a copy of the input doxygen file. CMake will generate a custom doxyfile
    configure_file(${DOXYFILE_IN} ${DOXYFILE_CMAKE} @ONLY)

    # Command to generate the documentation
    add_custom_target(documentation 
        ${DOXYGEN_EXECUTABLE} ${DOXYFILE_CMAKE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs)
endif()