add_library(Mat3x2Tests OBJECT)

target_sources(
        Mat3x2Tests PRIVATE
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

        Mat3x2TestSetup.h
)

target_include_directories(
        Mat3x2Tests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Mat3x2Tests PRIVATE
        FalconMathTestSetup
)