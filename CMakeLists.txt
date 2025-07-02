cmake_minimum_required(VERSION 3.10)
project(blackjack)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include headers
include_directories(include)

# Collect all source files
file(GLOB SOURCES "src/*.cpp")

# Build executable
add_executable(blackjack ${SOURCES})
