cmake_minimum_required(VERSION 3.16)
project(Mako)

set(CMAKE_CXX_STANDARD 17)

# SDL2 build options
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)

# Add SDL2
add_subdirectory(external/SDL2)

# ImGui sources
set(IMGUI_DIR external/imgui)
file(GLOB IMGUI_SOURCES
        ${IMGUI_DIR}/*.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)

# Create executable
add_executable(${PROJECT_NAME} WIN32
        src/main.cpp
        ${IMGUI_SOURCES}
        src/keys.h
        src/settings.h
        src/input_handler.h
        src/gui.h
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        external/SDL2/include
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
        SDL2::SDL2-static
)