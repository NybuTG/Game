cmake_minimum_required(VERSION 3.8)

project(
    Game
    VERSION 1.0
    DESCRIPTION "My Game"
    LANGUAGES CXX C
)

include_directories(include)
file(GLOB_RECURSE SOURCE_CODE CONFIGURE_DEPENDS "src/*.c" "src/*.cpp")

set(CMAKE_EXE_LINKER_FLAGS "-lfmt -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(ROOT "/home/derkjanw/Documents/game")

add_definitions(
    -DGL_GLEXT_PROTOTYPES
    -DROOT="${ROOT}"
)

add_executable(
    out
    ${SOURCE_CODE}
)