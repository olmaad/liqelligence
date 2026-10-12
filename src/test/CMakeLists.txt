# tests
set(TARGET_NAME ${PROJECT_NAME}_test)
set(TARGET_NAME_TEST ${TARGET_NAME} PARENT_SCOPE)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

set(FILES
    ${HEADERS}
    ${SOURCES}
)

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}"
    PREFIX Src
    FILES ${FILES}
)

add_executable(${TARGET_NAME} ${FILES})

target_include_directories(${TARGET_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${PROJECT_NAME}_test
    PRIVATE
        ${TARGET_NAME_LIB}
        Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(${TARGET_NAME})

target_precompile_headers(${PROJECT_NAME}_test
    PRIVATE
        "${CMAKE_SOURCE_DIR}/src/precompiled.hpp"
)