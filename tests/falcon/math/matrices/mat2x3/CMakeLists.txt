add_library(Mat2x3Tests OBJECT)

target_sources(
        Mat2x3Tests PRIVATE
        AccessAndMutationTests.cpp
        AdditionTests.cpp
        AliasTests.cpp
        ConstantTests.cpp
        DivisionTests.cpp
        EqualityTests.cpp
        InitializationTests.cpp
        MultiplicationTests.cpp
        NegationTests.cpp
        StringRepresentationTests.cpp
        SubtractionTests.cpp
        TransposeTests.cpp
        TypeConversionTests.cpp
        UtilityTests.cpp

        Mat2x3TestSetup.h
)

target_include_directories(
        Mat2x3Tests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Mat2x3Tests PRIVATE
        FalconMathTestSetup
)