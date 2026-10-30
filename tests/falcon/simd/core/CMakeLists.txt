add_executable(FalconSIMDCoreTests
        Simd128/ArithmeticTests.cpp
        Simd128/ComparisonTests.cpp
        # Simd128/ConversionCtorTests.cpp # TODO: Enable after creating a conversion ctor
        Simd128/GetterSetterTests.cpp
        Simd128/LoadStoreTests.cpp
        Simd128/BitwiseOperationTests.cpp
        Simd128/BlendTests.cpp
        Simd128/ShuffleTests.cpp
        Simd128/ConstructorTests.cpp
        Simd128/UtilTests.cpp
        Simd128/BasicMathOperationTests.cpp

        Simd256/ArithmeticTests.cpp
        Simd256/ComparisonTests.cpp
        Simd256/GetterSetterTests.cpp
        Simd256/LoadStoreTests.cpp
        Simd256/BitwiseOperationTests.cpp
        Simd256/BlendTests.cpp
        Simd256/ShuffleTests.cpp
        Simd256/ConstructorTests.cpp
        Simd256/UtilTests.cpp
        Simd256/BasicMathOperationTests.cpp
)

target_compile_options(FalconSIMDCoreTests PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/bigobj>)
target_include_directories(FalconSIMDCoreTests PRIVATE "${FALCON_SIMD_TEST_ROOT_DIR}/include")

target_link_libraries(FalconSIMDCoreTests PRIVATE FalconSIMDTestSetup)

if (FALCON_SIMD_COMBINED_TEST_RUN)
    add_test(NAME FalconSIMDMemoryTestSuite COMMAND FalconSIMDCoreTests)
else ()
    gtest_discover_tests(FalconSIMDCoreTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
endif ()