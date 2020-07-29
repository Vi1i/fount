cmake_minimum_required(VERSION 3.7)
project(fountd VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE(FindPkgConfig)
pkg_search_module(SYSTEMD REQUIRED libsystemd)

add_executable(fountd
    src/app.cpp
)

#Set target properties
target_include_directories(fountd
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        Fount
        ${SYSTEMD_INCLUDE_DIRS}
)

target_link_libraries(fountd
  PUBLIC
  PRIVATE
  ${SYSTEMD_LIBRARIES}
  Fount
)
