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
find_program(CLANG_FORMAT_EXE NAMES "clang-format")
if(NOT CLANG_FORMAT_EXE)
    message(FATAL_ERROR "clang-format not found.")
endif()

add_custom_target(verify-format
    COMMAND ${CLANG_FORMAT_EXE} -style=google -output-replacements-xml ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Source_Files/*.h > /dev/null
    COMMAND ${CMAKE_COMMAND} -E echo "[ :\\) ] Code formatting check completed!"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Verifying code formatting..."
)


# Add dependencies to ensure formatting is checked before building
add_dependencies(Banana verify-format)




