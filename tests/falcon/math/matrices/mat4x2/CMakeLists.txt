add_library(Mat4x2Tests OBJECT)

target_sources(
        Mat4x2Tests PRIVATE
        AliasTests.cpp
        AccessAndMutationTests.cpp
        AdditionTests.cpp
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

        Mat4x2TestSetup.h
)

target_include_directories(
        Mat4x2Tests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Mat4x2Tests PRIVATE
        FalconMathTestSetup
)