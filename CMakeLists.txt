cmake_minimum_required(VERSION 3.10)
project(monster_spil)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Add executable
add_executable(monster_spil
    main.cpp
    character.cpp
    monsters.cpp
    combat.cpp
    menu.cpp
    item.cpp
    caves.cpp
)

# Include directories (if needed for headers)
target_include_directories(monster_spil PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

