add_library(FalconMathTestSetup INTERFACE
        include/CommonSetup.h
        include/DoxygenGroups.h
        include/utils/FloatEquals.h
        include/utils/MatrixUtils.h
        include/utils/TypeUtils.h
        include/utils/VectorUtils.h
)

target_include_directories(FalconMathTestSetup INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(FalconMathTestSetup INTERFACE FalconTestSetup)

add_subdirectory(common)
add_subdirectory(vectors)
add_subdirectory(quaternions)
add_subdirectory(matrices)