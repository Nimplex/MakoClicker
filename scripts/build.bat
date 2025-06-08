@echo off

if not exist build mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release

cd ..
echo Build complete! Executable in build/Release/

pause