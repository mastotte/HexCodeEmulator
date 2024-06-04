cmake_minimum_required(VERSION 3.22.1)

project(TheBanana LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Define the target (executable)
add_executable(TheBanana # Use the project name for consistency
    Source_Files/main.cpp
    Source_Files/BananaOS.cpp
    Source_Files/memory.cpp
    Source_Files/cpu.cpp
    Source_Files/gpu.cpp
)

# Link SDL2 libraries to the executable
target_link_libraries(TheBanana ${SDL2_LIBRARIES}) 

# Custom target for code formatting verification
add_custom_target(verify-format
    COMMAND clang-format -output-replacements-xml -style=file
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/*.h
    | grep -c '<replacement ' > /dev/null
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Checking code formatting..."
)
