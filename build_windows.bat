@echo off
setlocal

REM Builds the SFML project on Windows using CMake.
REM If you use vcpkg, set VCPKG_ROOT before running this file.

if defined VCPKG_ROOT (
    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake"
) else (
    cmake -S . -B build
)

if errorlevel 1 exit /b 1

cmake --build build --config Debug
if errorlevel 1 exit /b 1

echo.
echo Build complete. Executable should be in build\Debug\MySFMLProject.exe
