add_library(Vec3Tests OBJECT)

target_sources(
        Vec3Tests PRIVATE
        AccessAndMutationTests.cpp
        AliasTests.cpp
        ArithmeticOperationTests.cpp
        BooleanBitOperationTests.cpp
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
        RejectionTests.cpp
        StringRepresentationTests.cpp
        SwizzlingTests.cpp
        TypeConversionTests.cpp
        UtilityTests.cpp

        Vec3TestSetup.h
)

target_include_directories(
        Vec3Tests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Vec3Tests PRIVATE
        FalconMathTestSetup
)