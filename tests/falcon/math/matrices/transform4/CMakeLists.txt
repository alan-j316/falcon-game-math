add_library(Transform4Tests OBJECT)

target_sources(
        Transform4Tests PRIVATE
        AccessAndMutationTests.cpp
        InitializationTests.cpp
        InverseTests.cpp
        MultiplicationTests.cpp

        Transform4TestSetup.h
)

target_include_directories(
        Transform4Tests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)

target_link_libraries(
        Transform4Tests PRIVATE
        FalconMathTestSetup
)