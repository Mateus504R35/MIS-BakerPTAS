cmake_minimum_required(VERSION 3.16)
project(baker_ptas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BOOST_ROOT "" CACHE PATH "Diretorio raiz da biblioteca Boost")

add_executable(baker_ptas
    src/main.cpp
    src/graph.cpp
    src/io.cpp
    src/independent_set.cpp
    src/exact_mis.cpp
    src/planarity.cpp
)

target_include_directories(baker_ptas PRIVATE include)

if(BOOST_ROOT)
    target_include_directories(baker_ptas PRIVATE ${BOOST_ROOT})
endif()

target_compile_options(baker_ptas PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
)