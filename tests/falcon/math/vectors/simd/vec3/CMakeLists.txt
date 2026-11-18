add_library(Vec3SimdTests OBJECT)

target_sources(
        Vec3SimdTests PRIVATE
        AccessAndMutationTests.cpp
        AliasTests.cpp
        ArithmeticOperationTests.cpp
        #        BooleanBitOperationTests.cpp
        ComparisonTests.cpp
        ConstantsTests.cpp
        DistanceTests.cpp
        EqualityTests.cpp
        InitializationTests.cpp
        MagnitudeTests.cpp
        #        NormalizationTests.cpp
        PNormTests.cpp
        ProductTests.cpp
        ProjectionTests.cpp
        RawPointerTests.cpp
        #        RejectionTests.cpp
        #        StringRepresentationTests.cpp
        SwizzlingTests.cpp
        TypeConversionTests.cpp
        UtilityTests.cpp

        Vec3TestSetup.h
)

target_include_directories(
        Vec3SimdTests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Vec3SimdTests PRIVATE
        FalconMathTestSetup
)