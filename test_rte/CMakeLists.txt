# Generated test RTE sources (ArUnit gmock generator output, see
# bceutil/Scripts/generateTestRte.sh) for the SwcLceComManager and
# SwcLceMaster software components.
set(
    testRte_sourceFiles
    generated/Rte_SwcLceComManager.cpp
    generated/Rte_SwcLceComManager_Mock.cpp
    generated/Rte_SwcLceComManager_BufferDecorator.cpp
    generated/Rte_SwcLceComManager_TraceDecorator.cpp
    generated/Rte_SwcLceComManager_CanoeTraceDump.cpp
    generated/SwcLceComManager_FixtureBase.cpp
    generated/Rte_SwcLceMaster.cpp
    generated/Rte_SwcLceMaster_Mock.cpp
    generated/Rte_SwcLceMaster_BufferDecorator.cpp
    generated/Rte_SwcLceMaster_TraceDecorator.cpp
    generated/Rte_SwcLceMaster_CanoeTraceDump.cpp
    generated/SwcLceMaster_FixtureBase.cpp
)

add_library(test_rte STATIC ${testRte_sourceFiles})

target_include_directories(
    test_rte PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/generated
    # Hand-maintained RTE platform headers (kept outside the ArUnit output
    # directory so regeneration / -clean_output cannot delete them).
    ${CMAKE_CURRENT_SOURCE_DIR}/rte_platform
)

target_link_libraries(test_rte PUBLIC lib_gtest)
