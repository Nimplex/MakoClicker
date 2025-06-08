@echo off

if not exist external mkdir external
cd external

if not exist imgui (
    git clone --depth 1 https://github.com/ocornut/imgui.git imgui
    echo ImGui cloned successfully
) else (
    echo ImGui already exists
)

if not exist SDL2 (
    git clone --depth 1 --branch SDL2 https://github.com/libsdl-org/SDL.git SDL2
    echo SDL2 cloned successfully
) else (
    echo SDL2 already exists
)

cd ..
echo Dependencies setup complete!

pause