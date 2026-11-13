# SwcLceComManager software component
include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeSourceLists.txt)

add_library(
    swc_lce_com_manager STATIC
    ${SwcLceComManager_headerFiles}
    ${SwcLceComManager_sourceFiles}
)

target_include_directories(
    swc_lce_com_manager PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/test_rte/generated
)

add_subdirectory(test/gtest)
