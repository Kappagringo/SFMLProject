cmake_minimum_required(VERSION 3.28)
project(MySFMLProject)

set(CMAKE_CXX_STANDARD 17)
<<<<<<< HEAD
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML CONFIG REQUIRED COMPONENTS System Window Graphics Audio)

add_executable(MySFMLProject
        main.cpp
=======

# Use vcpkg's toolchain file to locate SFML and SFGUI
# if not specified globally in your IDE's settings:
# -DCMAKE_TOOLCHAIN_FILE="C:/Users/jdavis/ClionProjects/MySFMLProject/vcpkg/scripts/buildsystems/vcpkg.cmake"

find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics audio)
find_package(SFGUI CONFIG REQUIRED)

add_executable(MySFMLProject main.cpp
>>>>>>> e9ea8f4e26d3e58fbb38d61516859404e7f42a65
        game.cpp
        game.h
        cursor.cpp
        cursor.h
        menu.cpp
        menu.h)

target_link_libraries(MySFMLProject PRIVATE
<<<<<<< HEAD
        SFML::System
        SFML::Window
        SFML::Graphics
        SFML::Audio)

# Put runtime assets next to the executable so Debug/Release builds can run directly.
=======
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        SFGUI::SFGUI
)

# Copy the Nunito font to the build directory
>>>>>>> e9ea8f4e26d3e58fbb38d61516859404e7f42a65
add_custom_command(
        TARGET MySFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/nunito.ttf"
<<<<<<< HEAD
        "$<TARGET_FILE_DIR:MySFMLProject>/nunito.ttf")

add_custom_command(
        TARGET MySFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:MySFMLProject>/Assets")
=======
        $<TARGET_FILE_DIR:MySFMLProject>
)
# Copy Assets folder to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/Assets DESTINATION ${CMAKE_BINARY_DIR})

>>>>>>> e9ea8f4e26d3e58fbb38d61516859404e7f42a65
