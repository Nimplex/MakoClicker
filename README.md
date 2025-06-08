# Mako Autoclicker

A lightweight autoclicker application for Windows with both mouse and keyboard support. Built with SDL2 and ImGui.

## Quick Start (Pre-built Release)

1. Download the latest release from the [releases](https://github.com/Nimplex/MakoClicker/releases/) page
2. Extract the archive to your desired location
3. Run `Mako.exe`

## Building from Source

### Requirements

* Windows 10 or later (64-bit)
* Visual Studio 2019 or later (recommended) — includes MSVC compiler and C++ toolchain
  *(Alternatively, you can use other C++ compilers compatible with CMake, but Visual Studio is recommended for ease of use)*
* CMake 3.16 or higher
* Git (for fetching dependencies)

### 1. Clone the Repository

```bash
git clone https://github.com/Nimplex/MakoClicker
cd MakoClicker
```

### 2. Fetch Dependencies

Run the dependency script to automatically download ImGui and SDL2:

```bash
scripts/fetch_dependencies.bat
```

This will create an `external/` directory and clone the required libraries.

### 3. Build the Application

Use the build script for a quick Release build:

```bash
scripts/build.bat
```

Or build manually with CMake:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

The executable will be created in `build/Release/Mako.exe`.

## License

This project is licensed under MIT license, check out `LICENSE` file for more details.

## Disclaimer

This software is for educational and legitimate automation purposes only. Users are responsible for complying with the terms of service of any applications or games they use this software with. The developers are not responsible for any consequences resulting from the use of this software.
