
set(BINARY libFount_test)

add_executable(${BINARY}
    src/entry.cpp
)

target_link_libraries(${BINARY} PUBLIC core net gtest)

add_test(NAME ${BINARY} COMMAND ${BINARY})
