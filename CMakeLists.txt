cmake_minimum_required(VERSION 3.10)
project(cliptools)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(pbcopy src/pbcopy.cpp)
add_executable(pbpaste src/pbpaste.cpp)

install(TARGETS pbcopy pbpaste
    RUNTIME DESTINATION bin
)