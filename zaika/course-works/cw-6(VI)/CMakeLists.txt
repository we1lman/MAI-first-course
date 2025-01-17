cmake_minimum_required(VERSION 3.10)
project(BinaryTreeSearch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(main
        src/main.cpp
        src/Computer.cpp
)

add_executable(create_inventory
        src/create_inventory.cpp
        src/Computer.cpp
)
