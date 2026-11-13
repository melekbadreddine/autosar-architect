# Unit tests for the SwcLceComManager software component
set(
    SwcLceComManager_testFiles
    ${CMAKE_CURRENT_SOURCE_DIR}/SwcLceComManager_SmokeTest.cpp
)

add_executable(
    swc_lce_com_manager_test
    ${SwcLceComManager_testFiles}
    ${PROJECT_SOURCE_DIR}/lib/gtest/googlemock/src/gmock_main.cc
)

target_link_libraries(
    swc_lce_com_manager_test PRIVATE
    swc_lce_com_manager
    test_rte
)

add_test(NAME swc_lce_com_manager_test COMMAND swc_lce_com_manager_test)
