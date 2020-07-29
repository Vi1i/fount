cmake_minimum_required(VERSION 3.7)
project(net VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(net SHARED
    src/Socket.cpp
)

target_include_directories(net
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(net
  PUBLIC
  PRIVATE
)

set_target_properties(net PROPERTIES OUTPUT_NAME "YjornNet")

install (TARGETS net
    EXPORT YjornNetTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

write_basic_package_version_file(
    YjornNetConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)
install(EXPORT YjornNetTargets
    FILE YjornNetTargets.cmake
    NAMESPACE yjorn::
    DESTINATION lib/cmake/YjornNet
)

add_library(yjorn::net ALIAS net)
