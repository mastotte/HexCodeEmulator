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

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/Banana.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/memory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/cpu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/gpu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/*.h
)

find_program(CLANG_FORMAT "clang-format")
if(NOT CLANG_FORMAT)
    message(FATAL_ERROR "clang-format not found. Please install it.")
endif()

add_custom_target(format
    COMMAND ${CLANG_FORMAT} -style=Google -i ${SOURCE_FILES}
    COMMENT "Formatting source files..."
)

add_custom_target(verify-format
    COMMAND ${CLANG_FORMAT} -style=Google --dry-run --Werror ${SOURCE_FILES}
    COMMENT "Verifying code formatting against Google style..."
)

add_custom_target(check-format
    DEPENDS format verify-format
    COMMENT "Formatting and verifying source files..."
)

add_dependencies(Banana check-format)
