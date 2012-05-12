# Main CMakeLists file

cmake_minimum_required(VERSION 2.0)

project(PhantomMenace)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
add_subdirectory(src)
add_subdirectory(test)

enable_testing()

