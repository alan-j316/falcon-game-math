add_executable(FalconMathQuaternionsTests
        # Compilation Units
        ArithmeticOperationTests.cpp
        AccessAndMutationTests.cpp
        ConstantsTests.cpp
        EqualityTests.cpp
        InitializationTests.cpp
        QuaternionAlgebraTests.cpp
        TypeConversionTests.cpp
        UtilityTests.cpp
        VectorAlgebraTests.cpp

        # Headers
        include/QuaternionTestSetup.h
)
set_target_properties(FalconMathQuaternionsTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconMathQuaternionsTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconMathQuaternionsTests PROPERTIES CXX_EXTENSIONS OFF)

target_sources(
        FalconMathQuaternionsTests

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${FALCON_ROOT_INCLUDE_DIR}
        FILES
        ${SetupHeaderFiles}
        ${TestUtilities}
)

target_compile_options(FalconMathQuaternionsTests INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

target_link_libraries(
        FalconMathQuaternionsTests
        PRIVATE
        FalconMathTestSetup
)

target_precompile_headers(
        FalconMathQuaternionsTests
        REUSE_FROM
        FalconMathCommonTests
)


##############################
# Death Tests

add_executable(FalconMathQuaternionsDeathTests
        # Compilation Units
        death-tests/ArithmeticOperationDeathTests.cpp
        death-tests/QuaternionAlgebraTests.cpp

        # Headers
        include/QuaternionTestSetup.h
)
set_target_properties(FalconMathQuaternionsDeathTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconMathQuaternionsDeathTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconMathQuaternionsDeathTests PROPERTIES CXX_EXTENSIONS OFF)

target_sources(
        FalconMathQuaternionsDeathTests

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${FALCON_ROOT_INCLUDE_DIR}
        FILES
        ${SetupHeaderFiles}
        ${TestUtilities}
)

target_compile_options(FalconMathQuaternionsDeathTests INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

target_link_libraries(
        FalconMathQuaternionsDeathTests
        PRIVATE
        FalconMathTestSetup
)

target_precompile_headers(
        FalconMathQuaternionsDeathTests
        REUSE_FROM
        FalconMathCommonTests
)


include(GoogleTest)
if (FALCON_COMBINED_TEST_RUN)
    add_test(NAME FALCONQuaternionsTestSuite COMMAND FalconMathQuaternionsTests)
    add_test(NAME FALCONQuaternionsDeathTestSuite COMMAND FalconMathQuaternionsDeathTests)
else ()
    gtest_discover_tests(FalconMathQuaternionsTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
    gtest_discover_tests(FalconMathQuaternionsDeathTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
endif ()