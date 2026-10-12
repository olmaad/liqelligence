# docs and doxygen
set(TARGET_NAME ${PROJECT_NAME}_docs)
set(TARGET_NAME_DOCS ${TARGET_NAME} PARENT_SCOPE)

set(DOCS_INPUT "${CMAKE_CURRENT_SOURCE_DIR}")
set(DOCS_OUTPUT "${CMAKE_BINARY_DIR}/doxygen")
set(DOCS_OUTPUT_GENERATED "${DOCS_OUTPUT}/generated")

configure_file("${DOCS_INPUT}/doxygen_config.template" "${DOCS_OUTPUT}/doxygen_config" @ONLY)

file(GLOB_RECURSE DOCS CONFIGURE_DEPENDS
    "${DOCS_INPUT}/*"
)

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}"
    PREFIX Docs
    FILES ${DOCS}
)

add_custom_target(${PROJECT_NAME}_docs
    ALL
    COMMAND doxygen -q "${DOCS_OUTPUT}/doxygen_config"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    SOURCES ${DOCS}
)