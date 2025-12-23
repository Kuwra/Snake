cmake_minimum_required(VERSION 3.11)
project(Snake)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -pedantic -Werror=return-type -Werror=parentheses -Werror=vla -Werror=array-bounds -Wcast-qual -Wmaybe-uninitialized )

if (UNIX)
    set ( CMAKE_MODULES_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULES_PATH})
    set ( CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/SFML" ${CMAKE_PREFIX_PATH})
endif(UNIX)

if (WIN32)
    set( SFML_STATIC_LIBRARIES TRUE )
    set ( SFML_DIR "C:/msys64/ucrt64/lib/cmake/SFML")
endif(WIN32)

find_package(SFML 2.6 COMPONENTS system window graphics audio REQUIRED)


add_executable(Snake 
        src/main.cpp
        src/Snake.cpp
        src/Snake.h
        src/Food.cpp
        src/Food.h
        src/GameController.cpp
        src/GameController.h)

target_link_libraries(Snake sfml-graphics sfml-window sfml-system sfml-audio)

add_custom_command(TARGET Snake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:Snake>/resources
)
