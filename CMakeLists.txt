
cmake_minimum_required(VERSION 3.22.1)

project(TheBanana LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    main.cpp
    cpu.cpp
)