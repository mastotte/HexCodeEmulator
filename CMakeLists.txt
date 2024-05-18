cmake_minimum_required(VERSION 3.22.1)

project(TheBanana LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Define the target (executable)
add_executable(TheBanana # Use the project name for consistency
    main.cpp
    cpu.cpp
)

# Link SDL2 libraries to the executable
target_link_libraries(TheBanana ${SDL2_LIBRARIES}) 