add_executable(FalconSIMDUtilsTests
        TypeTraitsTests.cpp
        SimdUtilsTests.cpp
)

set_target_properties(FalconSIMDUtilsTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconSIMDUtilsTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconSIMDUtilsTests PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(FalconSIMDUtilsTests PRIVATE FalconSIMDTestSetup)

if (FALCON_SIMD_COMBINED_TEST_RUN)
    add_test(NAME FalconSIMDUtilsTestSuite COMMAND FalconSIMDUtilsTests)
else ()
    gtest_discover_tests(FalconSIMDUtilsTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
endif ()