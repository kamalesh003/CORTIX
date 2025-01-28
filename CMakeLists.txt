cmake_minimum_required(VERSION 3.14)
project(CortiX LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
find_package(Threads REQUIRED)

# Include directories
include_directories(src)

# Source files
file(GLOB CORTIX_SOURCES
    "src/neuromorphic/*.cpp"
    "src/semantic_engine/*.cpp"
    "src/core/*.cpp"
)

# Executable
add_executable(cortix src/core/main.cpp ${CORTIX_SOURCES})
target_link_libraries(cortix PRIVATE Threads::Threads)

