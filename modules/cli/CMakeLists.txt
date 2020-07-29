cmake_minimum_required(VERSION 3.7)
project(cli VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cli
    src/app.cpp
)

#Set target properties
target_include_directories(cli
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        yjorn::sys
        yjorn::fount::core
)

target_link_libraries(cli
    PUBLIC
    PRIVATE
    yjorn::fount::core
    yjorn::sys
)

set_target_properties(cli PROPERTIES OUTPUT_NAME "fount-cli")

install (TARGETS cli
    EXPORT FountCliTargets
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
