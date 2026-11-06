add_library(CVec2Tests OBJECT)

target_sources(
        CVec2Tests PRIVATE
        AccessAndMutationTests.cpp
        AliasTests.cpp
        ArithmeticOperationTests.cpp
        BooleanBitOperationTests.cpp
        ConversionTests.cpp
        ComparisonTests.cpp
        ConstantsTests.cpp
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

        CVec2TestSetup.h
)

target_include_directories(
        CVec2Tests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)


target_link_libraries(
        CVec2Tests PRIVATE
        FalconMathTestSetup
)