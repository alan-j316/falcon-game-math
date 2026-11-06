add_library(Mat2x4Tests OBJECT)

target_sources(
        Mat2x4Tests PRIVATE
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

        Mat2x4TestSetup.h
)

target_include_directories(
        Mat2x4Tests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Mat2x4Tests PRIVATE
        FalconMathTestSetup
)