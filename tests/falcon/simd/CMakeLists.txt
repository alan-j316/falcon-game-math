add_library(FalconSIMDTestSetup INTERFACE
        include/CommonSetup.h
        include/DoxygenGroups.h
        include/SIMDTestSetup.h
        include/utils/FloatEquals.h
        include/utils/TypeUtils.h
)

target_include_directories(FalconSIMDTestSetup INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(FalconSIMDTestSetup INTERFACE FalconTestSetup)

# Error with avx1-10 invalid combination
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(FalconSIMDTestSetup INTERFACE -Wno-invalid-feature-combination)
endif ()

add_subdirectory(utils)
add_subdirectory(core)
