add_executable(
        FalconMathUtilsTests

        BoundsTests.cpp
        InterpolationTests.cpp
        VecUtilsSetup.h
)


target_include_directories(
        FalconMathUtilsTests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)


target_link_libraries(
        FalconMathUtilsTests PRIVATE
        FalconMathTestSetup
)

include(GoogleTest)
# Runs the test binary as a single test
if (FALCON_COMBINED_TEST_RUN)
    add_test(NAME FalconMathUtilsTestSuite COMMAND FalconMathUtilsTests)
else ()
    gtest_discover_tests(FalconMathUtilsTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
endif ()
