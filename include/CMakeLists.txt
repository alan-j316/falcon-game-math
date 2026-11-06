set(FALCON_LIBRARY_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(FALCON_LIB_NAME Falcon)
set(FALCON_INTERNAL_TARGET_SUFFIX _Internal)

add_subdirectory(falcon/core)
add_subdirectory(falcon/simd)
add_subdirectory(falcon/math)

# Library Options
option(FALCON_FORCE_LEFT_HANDED "Use Left-Handed Coordinate System in Falcon Game Math")

add_library(${FALCON_LIB_NAME} INTERFACE
        falcon/Falcon.h
)
target_compile_features(${FALCON_LIB_NAME}  INTERFACE cxx_std_20)
add_library(${FALCON_LIB_NAME}::${FALCON_LIB_NAME} ALIAS ${FALCON_LIB_NAME})


target_link_libraries(${FALCON_LIB_NAME} INTERFACE
        ${FALCON_CORE_TARGET_NAME}
        ${FALCON_SIMD_TARGET_NAME}
        ${FALCON_MATH_TARGET_NAME}
)

target_include_directories(${FALCON_LIB_NAME} INTERFACE
        $<BUILD_INTERFACE:${FALCON_LIBRARY_ROOT_DIR}>
        $<INSTALL_INTERFACE:include>
)

if (FALCON_FORCE_LEFT_HANDED)
    message(STATUS "[Falcon]: Using Left-Handed Coordinate System")
    target_compile_definitions(${FALCON_LIB_NAME} INTERFACE FALCON_LEFT_HANDED)
    target_compile_definitions(${FALCON_LIB_NAME} INTERFACE FALCON_LEFT_HANDED)
else ()
    message(STATUS "[Falcon]: Using Right-Handed Coordinate System")
endif ()

# TODO: Update to an option
target_compile_options(${FALCON_LIB_NAME} INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict>)
