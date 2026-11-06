add_library(Point3Tests OBJECT)

target_sources(
        Point3Tests PRIVATE
        ArithmeticOperationTests.cpp
        InitializationTests.cpp

        Point3TestSetup.h
)

target_include_directories(
        Point3Tests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Point3Tests PRIVATE
        FalconMathTestSetup
)