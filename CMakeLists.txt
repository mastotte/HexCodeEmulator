cmake_minimum_required(VERSION 3.22.1)

project(Banana LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Define the target (executable)
add_executable(Banana # Use the project name for consistency
    Source_Files/main.cpp
    Source_Files/Banana.cpp
    Source_Files/memory.cpp
    Source_Files/cpu.cpp
    Source_Files/gpu.cpp
)

# Link SDL2 libraries to the executable
target_link_libraries(Banana ${SDL2_LIBRARIES}) 

# Custom target for code formatting verification
add_custom_target(verify-format
    COMMAND clang-format -style=Google
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/*.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Checking code formatting against Google style..."
)

