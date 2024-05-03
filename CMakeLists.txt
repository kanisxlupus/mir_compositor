cmake_minimum_required(VERSION 3.23)
project(helloWorld)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FindPkgConfig)
pkg_check_modules(MIRAL miral REQUIRED)

add_executable(helloWorld helloWorld.cpp)

target_include_directories(helloWorld PUBLIC SYSTEM ${MIRAL_INCLUDE_DIRS})
target_link_libraries(		helloWorld				${MIRAL_LDFLAGS})
