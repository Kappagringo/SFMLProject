cmake_minimum_required(VERSION 3.28)
project(MySFMLProject)

set(CMAKE_CXX_STANDARD 17)

# Use vcpkg's toolchain file to locate SFML and SFGUI
# if not specified globally in your IDE's settings:
# -DCMAKE_TOOLCHAIN_FILE="C:/Users/jdavis/ClionProjects/MySFMLProject/vcpkg/scripts/buildsystems/vcpkg.cmake"

find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics audio)
find_package(SFGUI CONFIG REQUIRED)

add_executable(MySFMLProject main.cpp)

target_link_libraries(MySFMLProject PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        SFGUI::SFGUI
)
