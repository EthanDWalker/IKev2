cmake_minimum_required(VERSION 3.10)

# Project name and version
project(VPNServer VERSION 1.0 LANGUAGES C)

# Set the C standard
# set(CMAKE_C_STANDARD 99)  # or C11 if you prefer
# set(CMAKE_C_STANDARD_REQUIRED True)

# Define where the source and header files are located
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# Include the header files directory globally
include_directories(${INCLUDE_DIR})

# Add subdirectories for each module (file1, file2)
add_subdirectory(src)

# Optionally, set the binary output directory
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
