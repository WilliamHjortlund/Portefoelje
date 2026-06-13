cmake_minimum_required(VERSION 3.10)
project(monster_spil)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

add_executable(monster_spil
    main.cpp
    character.cpp
    monsters.cpp
    combat.cpp
    menu.cpp
    item.cpp
    caves.cpp
    status.cpp
)

target_include_directories(monster_spil PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link med threads for std::this_thread::sleep_for på Linux
find_package(Threads REQUIRED)
target_link_libraries(monster_spil Threads::Threads)