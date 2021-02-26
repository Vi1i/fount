cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(Fount VERSION 0.1.0.0 LANGUAGES CXX)

include(cmake/GitSubmoduleHandler.cmake)
include(cmake/GeneralConfigurations.cmake)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CMakeFindDependencyMacro)

enable_testing()
add_subdirectory(extern/googletest EXCLUDE_FROM_ALL)

add_subdirectory(modules/sys)
add_subdirectory(modules/net)
add_subdirectory(modules/core)
add_subdirectory(modules/cli)
add_subdirectory(modules/daemon)
add_subdirectory(modules/test)
