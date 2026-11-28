add_executable(
        FalconMathUtilsTests

        BoundsTests.cpp
        InterpolationTests.cpp
        NormalizationTests.cpp
        projection/SimdVec2.cpp
        projection/SimdVec3.cpp
        projection/Vec2.cpp
        projection/Vec3.cpp
        projection/Vec4.cpp
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


add_executable(FalconMathUtilsDeathTests
        DeathTests.cpp
)

target_include_directories(
        FalconMathUtilsDeathTests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)

target_link_libraries(
        FalconMathUtilsDeathTests PRIVATE
        FalconMathTestSetup
)


include(GoogleTest)
# Runs the test binary as a single test
if (FALCON_COMBINED_TEST_RUN)
    add_test(NAME FalconMathUtilsTestSuite COMMAND FalconMathUtilsTests)
    add_test(NAME FalconMathUtilsDeathTestSuite COMMAND FalconMathUtilsDeathTests)
else ()
    gtest_discover_tests(FalconMathUtilsTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
    gtest_discover_tests(FalconMathUtilsDeathTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
endif ()
