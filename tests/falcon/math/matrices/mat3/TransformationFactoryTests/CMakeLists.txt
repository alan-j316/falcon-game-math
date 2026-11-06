add_library(Mat3TransformTests OBJECT)

target_sources(
        Mat3TransformTests PRIVATE
        AffineTests.cpp
        InvolutionTests.cpp
        ReflectionTests.cpp
        RotationTests.cpp
        ScaleTests.cpp
        ShearTests.cpp
)

target_include_directories(
        Mat3TransformTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${FALCON_TEST_ROOT_DIR}/include
)

target_link_libraries(
        Mat3TransformTests PRIVATE
        FalconMathTestSetup
)