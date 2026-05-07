# SFMLProject

A small SFML game prototype with a main menu, loading screen, and an empty playable winter scene.

## What changed

- Added a playable `New Game` flow.
- Added a short loading screen before gameplay starts.
- Added a controllable roaming character in an empty winter area.
- Added `build_windows.bat` to configure and build the executable with CMake.
- Added `run_game.bat` to launch the built executable.
- Updated `CMakeLists.txt` so the build creates `MySFMLProject.exe` and copies `Assets` plus `nunito.ttf` next to the executable.

## Controls

- `WASD` or arrow keys: move the character
- `Esc`: return to the main menu

## Build on Windows

Install SFML through vcpkg or another CMake-compatible setup.

If using vcpkg, make sure `VCPKG_ROOT` is set, then run:

```bat
build_windows.bat
```

After building, run:

```bat
run_game.bat
```

The executable should be created at:

```txt
build\Debug\MySFMLProject.exe
```
