include(GoogleTest)

# For faster CI/CD unit-tests on push are only run with essential types rather than the full type permutation.
option(NONCOMPREHENSIVE "Run Unit tests with essential type matrix only")
option(FALCON_COMBINED_TEST_RUN "Runs entire test binaries as unified tests for fgm")
option(FALCON_SIMD_COMBINED_TEST_RUN "Runs entire test binaries as unified tests for falcon simd")
set(ENV{FALCON_SIMD_TEST_FLAG} "AUTO") # SIMD Test Flags for Falcon Math Suite

# Add Project Sanitizers to Gtest
if (TARGET gtest AND (FALCON_TESTS OR FALCON_SIMD_TESTS))
    target_link_libraries(gtest PRIVATE ${PROJECT_NAME}-ProjectSanitizers)
    target_link_libraries(gmock PRIVATE ${PROJECT_NAME}-ProjectSanitizers)
    target_link_libraries(gtest_main PRIVATE ${PROJECT_NAME}-ProjectSanitizers)
endif ()


add_library(FalconTestSetup INTERFACE)
target_link_libraries(
        FalconTestSetup INTERFACE

        GTest::gtest
        GTest::gtest_main
        Falcon::Falcon
        ${PROJECT_NAME}-StrictWarnings
        ${PROJECT_NAME}-ProjectSanitizers
)
target_compile_features(FalconTestSetup INTERFACE cxx_std_20)

AddCompilerFlag(FalconTestSetup INTERFACE ${FALCON_SIMD_MODE})
target_compile_definitions(FalconTestSetup INTERFACE $<$<CONFIG:Debug>:ENABLE_DEBUG_TESTS>)


if (NONCOMPREHENSIVE)
    message(STATUS "[Falcon]: Running only non-comprehensive tests")
    target_compile_definitions(FalconTestSetup INTERFACE NONCOMPREHENSIVE)
    target_compile_definitions(FalconTestSetup INTERFACE $ENV{FALCON_SIMD_TEST_FLAG})
endif ()

if (FALCON_CORE_TESTS)
    message(STATUS "[Falcon]: Core Library tests are enabled")
    add_subdirectory(falcon/core)
endif ()

if (FALCON_TESTS)
    message(STATUS "[Falcon]: Game Math tests are enabled")
    add_subdirectory(falcon/math)
endif ()

if (FALCON_SIMD_TESTS)
    message(STATUS "[Falcon]: SIMD tests are enabled")
    add_subdirectory(falcon/simd)
endif ()
