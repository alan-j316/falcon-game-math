add_library(Vec2SimdTests OBJECT)

target_sources(
        Vec2SimdTests PRIVATE
        AccessAndMutationTests.cpp
        AliasTests.cpp
        ArithmeticOperationTests.cpp
        BooleanBitOperationTests.cpp
        ComparisonTests.cpp
        ConstantsTests.cpp
        ConversionTests.cpp
        DistanceTests.cpp
        EqualityTests.cpp
        InitializationTests.cpp
        MagnitudeTests.cpp
        NormalizationTests.cpp
        PNormTests.cpp
        ProductTests.cpp
        ProjectionTests.cpp
        RawPointerTests.cpp
        RejectionTests.cpp
        StringRepresentationTests.cpp
        SwizzlingTests.cpp
        TypeConversionTests.cpp
        UtilityTests.cpp

        Vec2TestSetup.h
)

target_include_directories(
        Vec2SimdTests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Vec2SimdTests PRIVATE
        FalconMathTestSetup
)