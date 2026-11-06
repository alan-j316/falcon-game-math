add_library(Mat2Tests OBJECT)

target_sources(
        Mat2Tests PRIVATE
        AccessAndMutationTests.cpp
        AdditionTests.cpp
        AliasTests.cpp
        ConstantTests.cpp
        DeterminantTests.cpp
        DivisionTests.cpp
        EqualityTests.cpp
        InitializationTests.cpp
        InverseTests.cpp
        MultiplicationTests.cpp
        NegationTests.cpp
        StringRepresentationTests.cpp
        SubtractionTests.cpp
        TraceTests.cpp
        TransposeTests.cpp
        TypeConversionTests.cpp
        UtilityTests.cpp

        Mat2TestSetup.h
)

target_include_directories(
        Mat2Tests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)

add_subdirectory(TransformationFactoryTests)

target_link_libraries(
        Mat2Tests PRIVATE
        FalconMathTestSetup
)