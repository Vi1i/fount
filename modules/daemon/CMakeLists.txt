cmake_minimum_required(VERSION 3.7)
project(fountd VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog REQUIRED)

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
        ${SYSTEMD_INCLUDE_DIRS}
        #spdlog::spdlog
        ${SPDLOG_INCLUDEDIR}
        yjorn::sys
        yjorn::net
        yjorn::fount::core
)

target_link_libraries(fountd
    PUBLIC
    PRIVATE
    ${SYSTEMD_LIBRARIES}
    spdlog::spdlog
    yjorn::fount::core
    yjorn::sys
    yjorn::net
)

set_target_properties(fountd PROPERTIES OUTPUT_NAME "fountd")

install (TARGETS fountd
    EXPORT FountdTargets
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
