# core library
set(TARGET_NAME ${PROJECT_NAME}_lib)
set(TARGET_NAME_LIB ${TARGET_NAME} PARENT_SCOPE)

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

add_library(${TARGET_NAME} ${FILES} ${LIQELLIGENCE_COMMON_FILES})

target_include_directories(${TARGET_NAME}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}"
    PRIVATE
        GLEW::glew
        glm::glm
        glfw
        lodepng
)

target_link_libraries(${TARGET_NAME}
    PRIVATE
        GLEW::glew
        glm::glm
        glfw
        lodepng
)

target_precompile_headers(${TARGET_NAME}
    PRIVATE
        "${LIQELLIGENCE_PRECOMPILE_HEADERS}"
)