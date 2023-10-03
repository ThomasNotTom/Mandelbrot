cmake_minimum_required(VERSION 3.26)
project(Test)

set(CMAKE_CXX_STANDARD 23)

add_executable(Test main.cpp
        ComplexNumber.h
        ColorConvert.h)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(Test
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)


find_package(SDL2_image CONFIG REQUIRED)
target_link_libraries(Test PRIVATE
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,
        SDL2_image::SDL2_image,
        SDL2_image::SDL2_image-static>
)