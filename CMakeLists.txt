cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(TheFount VERSION 0.1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_CPPLINT "cpplint")

include(GNUInstallDirs)

add_subdirectory(Fount)
add_subdirectory(fountd)
add_subdirectory(fount-cli)
