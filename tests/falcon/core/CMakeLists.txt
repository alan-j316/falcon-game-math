add_executable(FalconCoreTests)
set_target_properties(FalconCoreTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconCoreTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconCoreTests PROPERTIES CXX_EXTENSIONS OFF)

target_sources(
        FalconCoreTests
        PRIVATE
        traits/TypeHelpersTests.cpp
)

target_compile_options(FalconCoreTests INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

target_precompile_headers(
        FalconCoreTests
        PUBLIC

        <gtest/gtest.h>
        <limits>
        <concepts>
        <cstddef>
        <type_traits>
)

target_link_libraries(FalconCoreTests PRIVATE FalconTestSetup Falcon::Falcon)

if (FALCON_COMBINED_TEST_RUN)
    add_test(NAME FalconCoreTestSuite COMMAND FalconCoreTests)
else ()
    gtest_discover_tests(FalconCoreTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
endif ()