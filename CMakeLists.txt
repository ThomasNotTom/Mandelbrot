cmake_minimum_required(VERSION 3.26)
project(Test)

set(SDL2_INCLUDE_DIR "/opt/homebrew/Cellar/sdl2/2.30.9/include/SDL2")
set(SDL2_LIBRARY "/opt/homebrew/Cellar/sdl2/2.30.9/lib/libSDL2.dylib")
set(SDL2_IMAGE_INCLUDE_DIR "/opt/homebrew/Cellar/sdl2_image/2.8.2_2/include/SDL2")
set(SDL2_IMAGE_LIBRARY "/opt/homebrew/Cellar/sdl2_image/2.8.2_2/lib/libSDL2_image.dylib")

set(CMAKE_CXX_STANDARD 23)

add_executable(Test main.cpp ComplexNumber.h ColorConvert.h)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

target_link_libraries(Test PRIVATE ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

