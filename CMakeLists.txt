cmake_minimum_required(VERSION 4.0)

project(liqelligence LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# vcpkg dependencies
include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(lodepng CONFIG REQUIRED)
find_package(Catch2 3 CONFIG REQUIRED)

# common files
set(LIQELLIGENCE_PRECOMPILE_HEADERS
    "${CMAKE_SOURCE_DIR}/src/precompiled.hpp"
)

set(LIQELLIGENCE_COMMON_FILES
    ${LIQELLIGENCE_PRECOMPILE_HEADERS}
)

# sub-lists
add_subdirectory(src/lib)
add_subdirectory(src/game)
add_subdirectory(src/test)
add_subdirectory(res)
add_subdirectory(docs)

# platform specific
if(MSVC)
    set_property(DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME_GAME})
endif()
