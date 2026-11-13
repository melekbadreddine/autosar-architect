# Unit tests for the SwcLceMaster software component
set(
    SwcLceMaster_testFiles
    ${CMAKE_CURRENT_SOURCE_DIR}/SwcLceMaster_SmokeTest.cpp
)

add_executable(
    swc_lce_master_test
    ${SwcLceMaster_testFiles}
    ${PROJECT_SOURCE_DIR}/lib/gtest/googlemock/src/gmock_main.cc
)

target_link_libraries(
    swc_lce_master_test PRIVATE
    swc_lce_master
    test_rte
)

add_test(NAME swc_lce_master_test COMMAND swc_lce_master_test)
