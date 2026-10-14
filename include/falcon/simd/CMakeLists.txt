set(FALCON_SIMD_TARGET_NAME FalconSIMD${FLCN_INTERNAL_TARGET_SUFFIX})
add_library(${FALCON_SIMD_TARGET_NAME} INTERFACE
        core/Simd128.h
        core/RegisterTraits.h
        core/x86/Simd128SSE.h
        core/x86/Simd128SSE.inl
        core/x86/Simd256SSE.h
        core/x86/Simd256SSE.inl
        core/x86/Simd128X86Math.h
        core/x86/Simd128X86Math.inl
        core/x86/Simd256X86Math.h
        core/x86/Simd256X86Math.inl
        core/x86/Simd256AVX.h
        core/x86/Simd256AVX.inl
        core/x86/CustomX86Intrin.inl

        utils/SIMDUtils.h
        utils/TypeTraits.h
        utils/SimdTraits.h

        FalconSimd.h
        DoxygenGroups.h
)

target_compile_features(${FALCON_SIMD_TARGET_NAME} INTERFACE cxx_std_20)
# TODO: REMOVE PROJECT LINKAGE
target_link_libraries(${FALCON_SIMD_TARGET_NAME} INTERFACE
        ${FALCON_CORE_TARGET_NAME}
        ${PROJECT_NAME}-StrictWarnings
        ${PROJECT_NAME}-ProjectSanitizers
)

target_include_directories(${FALCON_SIMD_TARGET_NAME} INTERFACE ${FALCON_LIBRARY_ROOT_DIR})