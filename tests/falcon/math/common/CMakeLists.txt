add_executable(FalconMathCommonTests)
set_target_properties(FalconMathCommonTests PROPERTIES DISABLE_PRECOMPILE_HEADERS OFF)
set_target_properties(FalconMathCommonTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconMathCommonTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconMathCommonTests PROPERTIES CXX_EXTENSIONS OFF)

target_sources(
        FalconMathCommonTests PRIVATE
        MathTraitTests.cpp
        OperationStatusTests.cpp
        TrivialTypeTests.cpp
        UtilsTests.cpp
        WrapperTests.cpp
)

target_link_libraries(FalconMathCommonTests PRIVATE FalconMathTestSetup)

target_precompile_headers(
        FalconMathCommonTests
        PUBLIC
        <gtest/gtest.h>
        <iostream>
        <limits>
        <concepts>
        <cstddef>
        <type_traits>
)

if (FALCON_COMBINED_TEST_RUN)
    add_test(NAME FALCONCommonTestSuite COMMAND FalconMathCommonTests)
else ()
    gtest_discover_tests(FalconMathCommonTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
endif ()
