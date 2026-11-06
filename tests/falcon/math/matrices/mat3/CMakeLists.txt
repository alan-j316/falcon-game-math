add_library(Mat3Tests OBJECT)

target_sources(
        Mat3Tests PRIVATE
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

        Mat3TestSetup.h
)

target_include_directories(
        Mat3Tests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)

add_subdirectory(TransformationFactoryTests)

target_link_libraries(
        Mat3Tests PRIVATE
        FalconMathTestSetup
)