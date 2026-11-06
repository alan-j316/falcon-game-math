add_executable(FalconMathMatrixTests)
set_target_properties(FalconMathMatrixTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconMathMatrixTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconMathMatrixTests PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(FalconMathMatrixTests INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)


add_subdirectory(extra)
add_subdirectory(mat2)
add_subdirectory(mat2x3)
add_subdirectory(mat2x4)
add_subdirectory(mat3)
add_subdirectory(mat3x2)
add_subdirectory(mat3x4)
add_subdirectory(mat4)
add_subdirectory(mat4x2)
add_subdirectory(mat4x3)
add_subdirectory(transform4)

target_link_libraries(
        FalconMathMatrixTests
        PRIVATE
        FalconMathTestSetup

        # OBJs
        Mat2Tests
        Mat2TransformTests
        Mat2x3Tests
        Mat2x4Tests
        Mat3Tests
        Mat3TransformTests
        Mat3x2Tests
        Mat3x4Tests
        Mat4Tests
        Mat4x2Tests
        Mat4x3Tests
        Mat4TransformTests
        MatrixExtraOpTests
        Transform4Tests
)

target_precompile_headers(
        FalconMathMatrixTests
        REUSE_FROM
        FalconMathCommonTests
)


include(GoogleTest)

set_target_properties(
        Mat2Tests
        Mat2TransformTests
        Mat2x3Tests
        Mat2x4Tests
        Mat3Tests
        Mat3TransformTests
        Mat3x2Tests
        Mat3x4Tests
        Mat4Tests
        Mat4x2Tests
        Mat4x3Tests
        Mat4TransformTests
        MatrixExtraOpTests
        Transform4Tests
        PROPERTIES FOLDER "Test Intermediates/FALCON"
)


#####################################
## DEATH TESTS

add_executable(FalconMathMatrixDeathTests
        death-tests/Mat2.cpp
        death-tests/Mat2x3.cpp
        death-tests/Mat2x4.cpp
        death-tests/Mat3.cpp
        death-tests/Mat3x2.cpp
        death-tests/Mat3x4.cpp
        death-tests/Mat4.cpp
        death-tests/Mat4x2.cpp
        death-tests/Mat4x3.cpp
        death-tests/Transform4.cpp
)
set_target_properties(FalconMathMatrixDeathTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconMathMatrixDeathTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconMathMatrixDeathTests PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(FalconMathMatrixDeathTests INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

target_link_libraries(FalconMathMatrixDeathTests PRIVATE FalconMathTestSetup)
target_precompile_headers(FalconMathMatrixDeathTests REUSE_FROM FalconMathCommonTests)


#### GTEST
if (FALCON_COMBINED_TEST_RUN)
    add_test(NAME FALCONMatrixTestSuite COMMAND FalconMathMatrixTests)
    add_test(NAME FALCONMatrixDeathTestSuite COMMAND FalconMathMatrixDeathTests)
else ()
    gtest_discover_tests(FalconMathMatrixTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
    gtest_discover_tests(FalconMathMatrixDeathTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
endif ()
