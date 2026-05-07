@echo off
setlocal

if exist "build\Debug\MySFMLProject.exe" (
    start "" "build\Debug\MySFMLProject.exe"
) else if exist "cmake-build-debug\MySFMLProject.exe" (
    start "" "cmake-build-debug\MySFMLProject.exe"
) else (
    echo Executable not found. Run build_windows.bat first.
    pause
)
