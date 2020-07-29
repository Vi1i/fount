cmake_minimum_required(VERSION 3.7)
project(core VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(core SHARED
    src/Configuration.cpp
    src/Simulate.cpp
)

#Set target properties
target_include_directories(core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        src/
        yjorn::net
        yjorn::sys
)

target_link_libraries(core
  PUBLIC
  PRIVATE
  yjorn::net
  yjorn::sys
)
set_target_properties(core PROPERTIES OUTPUT_NAME "FountCore")

install (TARGETS core
    EXPORT FountCoreTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

write_basic_package_version_file(
    FountCoreConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(EXPORT FountCoreTargets
    FILE FountCoreTargets.cmake
    NAMESPACE yjorn::fount::
    DESTINATION lib/cmake/FountCore
)

add_library(yjorn::fount::core ALIAS core)
