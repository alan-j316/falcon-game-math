add_executable(FalconMathVectorTests)
set_target_properties(FalconMathVectorTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconMathVectorTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconMathVectorTests PROPERTIES CXX_EXTENSIONS OFF)

target_sources(
        FalconMathVectorTests

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${FALCON_ROOT_INCLUDE_DIR}
        FILES
        ${SetupHeaderFiles}
        ${TestUtilities}
)

target_compile_options(FalconMathVectorTests INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

# CONSTEXPR NON_SIMD
add_subdirectory(point2)
add_subdirectory(point3)
add_subdirectory(cvec2)
add_subdirectory(vec3)
add_subdirectory(vec4)
# SIMD
add_subdirectory(vec2)

target_link_libraries(
        FalconMathVectorTests
        PRIVATE
        FalconMathTestSetup

        # OBJs
        # CONSTEXPR
        Point2Tests
        Point3Tests
        CVec2Tests
        Vec3Tests
        Vec4Tests
        # SIMD
        Vec2Tests
)

target_precompile_headers(
        FalconMathVectorTests
        REUSE_FROM
        FalconMathCommonTests
)

set_target_properties(
        Point2Tests
        Point3Tests
        CVec2Tests
        Vec3Tests
        Vec4Tests

        Vec2Tests
        PROPERTIES FOLDER "Test Intermediates/FALCON"
)

###########################
### DEATH TESTS
add_executable(FalconMathVectorDeathTests
        cvec2/DeathTests.cpp # TODO: Add death tests here
        vec3/DeathTests.cpp
        vec4/DeathTests.cpp
        vec2/DeathTests.cpp
)
set_target_properties(FalconMathVectorDeathTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconMathVectorDeathTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconMathVectorDeathTests PROPERTIES CXX_EXTENSIONS OFF)

target_sources(
        FalconMathVectorDeathTests

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${FALCON_ROOT_INCLUDE_DIR}
        FILES
        ${SetupHeaderFiles}
        ${TestUtilities}
)

target_compile_options(FalconMathVectorDeathTests INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

target_link_libraries(
        FalconMathVectorDeathTests
        PRIVATE
        FalconMathTestSetup
)

target_precompile_headers(
        FalconMathVectorDeathTests
        REUSE_FROM
        FalconMathCommonTests
)


include(GoogleTest)
# Runs the test binary as a single test
if (FALCON_COMBINED_TEST_RUN)
    add_test(NAME FALCONVectorTestSuite COMMAND FalconMathVectorTests)
    add_test(NAME FALCONVectorDeathTestSuite COMMAND FalconMathVectorDeathTests)
else ()
    gtest_discover_tests(FalconMathVectorTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
    gtest_discover_tests(FalconMathVectorDeathTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
endif ()



