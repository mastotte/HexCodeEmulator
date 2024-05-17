
cmake_minimum_required(VERSION 3.22.1)

project(TheBanana LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(main ${SDL2_LIBRARIES})


add_executable(${PROJECT_NAME}
    main.cpp
    cpu.cpp
)