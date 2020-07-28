cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(TheFount VERSION 0.1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)

enable_testing()
add_subdirectory(lib/googletest)
add_subdirectory(Fount)
add_subdirectory(fountd)
add_subdirectory(fount-cli)
