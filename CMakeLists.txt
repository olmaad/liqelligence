cmake_minimum_required(VERSION 3.30)

project(liqelligence LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(Catch2 3 CONFIG REQUIRED)

file(GLOB_RECURSE LIB_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/*.hpp"
)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/*.cpp"
)

set(LIB_FILES
    ${LIB_HEADERS}
    ${LIB_SOURCES}
)

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}/src"
    FILES ${LIB_FILES}
)

add_library(${PROJECT_NAME}_lib ${LIB_FILES})

target_include_directories(${PROJECT_NAME}_lib PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib"
    GLEW::glew
    glm::glm
    glfw
)

target_link_libraries(${PROJECT_NAME}_lib PRIVATE
    GLEW::glew
    glm::glm
    glfw
)

file(GLOB_RECURSE GAME_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/game/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/game/*.hpp"
)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/game/*.cpp"
)

set(GAME_FILES
    ${GAME_HEADERS}
    ${GAME_SOURCES}
)

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}/src"
    FILES ${GAME_FILES}
)

add_executable(${PROJECT_NAME}_game ${GAME_FILES})

target_include_directories(${PROJECT_NAME}_game PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib"
)

target_link_libraries(${PROJECT_NAME}_game PRIVATE
    ${PROJECT_NAME}_lib
)

file(GLOB_RECURSE TEST_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/*.hpp"
)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/*.cpp"
)

set(TEST_FILES
    ${TEST_HEADERS}
    ${TEST_SOURCES}
)

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}/src"
    FILES ${TEST_FILES}
)

add_executable(${PROJECT_NAME}_test ${TEST_FILES})

target_include_directories(${PROJECT_NAME}_test PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test"
)

target_link_libraries(${PROJECT_NAME}_test PRIVATE
    ${PROJECT_NAME}_lib
    Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(${PROJECT_NAME}_test)

file(GLOB_RECURSE DOCS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/docs/*"
)

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES ${DOCS}
)

add_custom_target(${PROJECT_NAME}_docs SOURCES ${DOCS})

if(MSVC)
    set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME}_game)
endif()
