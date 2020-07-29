cmake_minimum_required(VERSION 3.7)
project(sys VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(sys SHARED
    src/System.cpp
)

target_include_directories(sys
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(sys
    PUBLIC
        stdc++fs
    PRIVATE
)

set_target_properties(sys PROPERTIES OUTPUT_NAME "YjornSys")

install (TARGETS sys
    EXPORT YjornSysTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

write_basic_package_version_file(
    YjornSysConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)
install(EXPORT YjornSysTargets
    FILE YjornSysTargets.cmake
    NAMESPACE yjorn::
    DESTINATION lib/cmake/YjornSys
)

add_library(yjorn::sys ALIAS sys)
