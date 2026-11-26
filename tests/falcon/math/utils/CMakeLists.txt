add_library(VecUtilsTests OBJECT)

target_sources(
        VecUtilsTests PRIVATE
        InterpolationTests.cpp

        VecUtilsSetup.h
)

target_include_directories(
        VecUtilsTests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include
)


target_link_libraries(
        VecUtilsTests PRIVATE
        FalconMathTestSetup
)