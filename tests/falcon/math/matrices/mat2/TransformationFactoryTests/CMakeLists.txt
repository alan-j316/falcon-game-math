add_library(Mat2TransformTests OBJECT)

target_sources(
        Mat2TransformTests PRIVATE
        ReflectionTests.cpp
        RotationTests.cpp
        ScaleTests.cpp
        ShearTests.cpp
)

target_include_directories(
        Mat2TransformTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${FALCON_TEST_ROOT_DIR}/include
)

target_link_libraries(
        Mat2TransformTests PRIVATE
        FalconMathTestSetup
)