cmake_minimum_required(VERSION 3.28)
project(MySFMLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML CONFIG REQUIRED COMPONENTS System Window Graphics Audio)

add_executable(MySFMLProject
        main.cpp
        game.cpp
        game.h
        cursor.cpp
        cursor.h
        menu.cpp
        menu.h)

target_link_libraries(MySFMLProject PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
        SFML::Audio)

# Put runtime assets next to the executable so Debug/Release builds can run directly.
add_custom_command(
        TARGET MySFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/nunito.ttf"
        "$<TARGET_FILE_DIR:MySFMLProject>/nunito.ttf")

add_custom_command(
        TARGET MySFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:MySFMLProject>/Assets")
