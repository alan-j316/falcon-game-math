add_library(MatrixExtraOpTests OBJECT)

target_sources(
        MatrixExtraOpTests PRIVATE
        comp/Mat2x3.cpp
        comp/Mat2x4.cpp
        comp/Mat3x2.cpp
        comp/Mat3x4.cpp
        comp/Mat4x2.cpp
        comp/Mat4x3.cpp

        geom/Mat2x3.cpp
        geom/Mat2x4.cpp
        geom/Mat3x2.cpp
        geom/Mat3x4.cpp
        geom/Mat4x2.cpp
        geom/Mat4x3.cpp
)

target_include_directories(
        MatrixExtraOpTests PRIVATE
        ${FALCON_TEST_ROOT_DIR}/include

)

target_link_libraries(
        MatrixExtraOpTests PRIVATE
        FalconMathTestSetup
)