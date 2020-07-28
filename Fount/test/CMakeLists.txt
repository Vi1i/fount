
set(BINARY libFount_test)

add_executable(${BINARY}
    src/entry.cpp
)

target_link_libraries(${BINARY} PUBLIC Fount gtest)

add_test(NAME ${BINARY} COMMAND ${BINARY})
