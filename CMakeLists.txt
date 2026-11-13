cmake_minimum_required(VERSION 3.10)
project(autosar_architect CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Unit test framework (googlemock / googletest)
add_subdirectory(lib/gtest)

# Generated test RTE (ArUnit gmock generator output)
add_subdirectory(test_rte)

# AUTOSAR software components
add_subdirectory(apps/light/lce/swc_lce_com_manager)
add_subdirectory(apps/light/lce/swc_lce_master)
