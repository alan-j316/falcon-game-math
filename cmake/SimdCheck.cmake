include_guard()

# Usage(Override): -DFALCON_SIMD_MODE=FALCON_ENABLE_AVX512F or set(FALCON_SIMD_MODE FALCON_ENABLE_AVX512F)
set(FALCON_SIMD_MODE "AUTO" CACHE STRING "AUTO, FALCON_ENABLE_AVX512EX, FALCON_ENABLE_AVX512F, FALCON_ENABLE_AVX2, FALCON_ENABLE_AVX, FALCON_ENABLE_SSE4 FALCON_ENABLE_SSE2, FALCON_ENABLE_NEON FALCON_DISABLE_SIMD")
set_property(CACHE FALCON_SIMD_MODE PROPERTY
        STRINGS
        "AUTO"
        "FALCON_ENABLE_AVX512EX"
        "FALCON_ENABLE_AVX512F"
        "FALCON_ENABLE_AVX2"
        "FALCON_ENABLE_AVX"
        "FALCON_ENABLE_SSE4"
        "FALCON_ENABLE_SSE2"
        "FALCON_ENABLE_NEON"
        "FALCON_DISABLE_SIMD"
)


# The FMA flag will be passed-down with no compile time checks if FMA is ENABLED.
# Auto will run a small program and detect FMA support.
# Note: ENABLED and AUTO put the -march=native flag for GCC, and Clang.
#       While FMA4 put the -mfma4 and FMA3 the -mfma flags respectively.
set(FALCON_SIMD_FMA "AUTO" CACHE STRING "AUTO, ENABLED, DISABLED, FMA4(AMD BullDozer), FMA3")
set_property(CACHE FALCON_SIMD_FMA PROPERTY STRINGS "AUTO" "ENABLED" "DISABLED" , "FMA4" , "FMA3")

include(CheckCXXSourceRuns)
include(CheckCXXCompilerFlag)

set(TEST_PROG_DIR "${PROJECT_SOURCE_DIR}/cmake/TestPrograms/")
string(RANDOM RANDOM_STR) # Random Suffix is required since the program same config like Clang-Debug LHS may try to access the same variable
set(TEST_COMPILE_DIR "${PROJECT_SOURCE_DIR}/cmake/TestPrograms/build/${CMAKE_CXX_COMPILER_ID}-${CMAKE_BUILD_TYPE}-${RANDOM_STR}")


#--------------------------------------------------------------------------------------
# Add the appropriate compiler flag and preprocessor definitions to target based
# on the provided config.
#
# ``Target``     The target to add the flag. Can be a library or executable.
# ``Visibility`` The linking visibility (PUBLIC PRIVATE INTERFACE)
# ``Config``     The Simd Configuration Flag to apply.
#                Options: AUTO(Detects Host System Capability), FALCON_ENABLE_AVX512EX,
#                         FALCON_ENABLE_AVX512F, FALCON_ENABLE_AVX2, FALCON_ENABLE_AVX,
##                        FALCON_ENABLE_SSE4 FALCON_ENABLE_SSE2, FALCON_ENABLE_NEON,
#                         FALCON_DISABLE_SIMD
#--------------------------------------------------------------------------------------
function(AddCompilerFlag Target Visibility Config)
    #--------------------------
    # AUTO SIMD FLAG DETECTION
    #--------------------------

    if (Config STREQUAL "AUTO")
        #----------------------------------------
        # SETUP COMPILER FLAGS FOR TEST PROGRAMS
        #----------------------------------------
        if (MSVC)
            set(TEST_FLAG_AVX512EX "/arch:AVX512")
            set(TEST_FLAG_AVX512F "/arch:AVX512")
            set(TEST_FLAG_AVX2 "/arch:AVX2")
            set(TEST_FLAG_AVX "/arch:AVX")
            set(TEST_FLAG_SSE4 "")
            set(TEST_FLAG_SSE2 "")
        else ()
            # GCC / Clang / AppleClang
            set(TEST_FLAG_AVX512EX "-mavx512f;-mavx512cd;-mavx512bw;-mavx512dq;-mavx512vl;-mfma")
            set(TEST_FLAG_AVX512F "-mavx512f")
            set(TEST_FLAG_AVX2 "-mavx2")
            set(TEST_FLAG_AVX "-mavx")
            set(TEST_FLAG_SSE4 "-msse4.2")
            set(TEST_FLAG_SSE2 "-msse2")
        endif ()

        #-------------------
        # TEST PROGRAM RUNS
        #-------------------
        message(STATUS "Running AVX512 Extension Tests")
        try_run(
                AVX512EX_RUNS
                AVX512EX_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/AVX512ExTest.cpp"
                CMAKE_FLAGS
                "-DCMAKE_CXX_STANDARD=17"
                "-DCMAKE_CXX_FLAGS=${TEST_FLAG_AVX512EX}"
                COMPILE_DEFINITIONS ${TEST_FLAG_AVX512EX}
        )
        if (AVX512EX_RUNS EQUAL 0)
            message(STATUS "AVX512BW/VL/DQ detection success!")
        else ()
            message(STATUS "AVX512BW/VL/DQ detection failed!")
        endif ()
        #        message(WARNING "AVX512EX Status: ${AVX512EX_COMPILES}")

        message(STATUS "Running AVX512 Foundation Tests")
        try_run(
                AVX512F_RUNS
                AVX512F_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/AVX512FTest.cpp"
                CMAKE_FLAGS
                "-DCMAKE_CXX_STANDARD=17"
                "-DCMAKE_CXX_FLAGS=${TEST_FLAG_AVX512F}"
                COMPILE_DEFINITIONS ${TEST_FLAG_AVX512F}
        )
        if (AVX512F_RUNS EQUAL 0)
            message(STATUS "AVX512F detection success!")
        else ()
            message(STATUS "AVX512F detection failed!")
        endif ()

        # AVX10 Has to be manually enabled
        #            try_run(
        #                    AVX10_RUNS
        #                    AVX10_COMPILES
        #                    "${PROJECT_SOURCE_DIR}/TestPrograms/build"
        #                    "${TEST_PROG_DIR}/AVX10Test.cpp"
        #                    CMAKE_FLAGS "-DCMAKE_CXX_STANDARD=17"
        #                    RUN_OUTPUT_VARIABLE AVX10_RUN_OUTPUT
        #            )

        message(STATUS "Running AVX2 Tests")
        try_run(
                AVX2_RUNS
                AVX2_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/AVX2Test.cpp"
                CMAKE_FLAGS
                "-DCMAKE_CXX_STANDARD=17"
                "-DCMAKE_CXX_FLAGS=${TEST_FLAG_AVX2}"
                COMPILE_DEFINITIONS ${TEST_FLAG_AVX2}
        )
        if (AVX2_RUNS EQUAL 0)
            message(STATUS "AVX2 detection success!")
        else ()
            message(STATUS "AVX2 detection failed!")
        endif ()

        message(STATUS "Running AVX Tests")
        try_run(
                AVX_RUNS
                AVX_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/AVXTest.cpp"
                CMAKE_FLAGS
                "-DCMAKE_CXX_STANDARD=17"
                "-DCMAKE_CXX_FLAGS=${TEST_FLAG_AVX}"
                COMPILE_DEFINITIONS ${TEST_FLAG_AVX}
        )
        if (AVX_RUNS EQUAL 0)
            message(STATUS "AVX detection success!")
        else ()
            message(STATUS "AVX detection failed!")
        endif ()

        message(STATUS "Running SSE4 Tests")
        try_run(
                SSE4_RUNS
                SSE4_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/SSE4Test.cpp"
                CMAKE_FLAGS
                "-DCMAKE_CXX_STANDARD=17"
                "-DCMAKE_CXX_FLAGS=${TEST_FLAG_SSE4}"
                COMPILE_DEFINITIONS ${TEST_FLAG_SSE4}
        )
        if (SSE4_RUNS EQUAL 0)
            message(STATUS "SSE4 detection success!")
        else ()
            message(STATUS "SSE4 detection failed!")
        endif ()

        message(STATUS "Running SSE2 Tests")
        try_run(
                SSE2_RUNS
                SSE2_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/SSETest.cpp"
                CMAKE_FLAGS
                "-DCMAKE_CXX_STANDARD=17"
                "-DCMAKE_CXX_FLAGS=${TEST_FLAG_SSE2}"
                COMPILE_DEFINITIONS ${TEST_FLAG_SSE2}
        )
        if (SSE2_RUNS EQUAL 0)
            message(STATUS "SSE2 detection success!")
        else ()
            message(STATUS "SSE2 detection failed!")
        endif ()

        message(STATUS "Running ARM Neon Tests")
        try_run(
                NEON_RUNS
                NEON_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/NeonTest.cpp"
                CMAKE_FLAGS
                "-DCMAKE_CXX_STANDARD=17"
        )
        if (NEON_RUNS EQUAL 0)
            message(STATUS "Neon detection success!")
        else ()
            message(STATUS "Neon detection failed!")
        endif ()


        # message(STATUS "COMPILATION")
        # message(STATUS "SSE2 ${SSE2_COMPILES}")
        # message(STATUS "SSE4 ${SSE4_COMPILES}")
        # message(STATUS "AVX ${AVX_COMPILES}")
        # message(STATUS "AVX2 ${AVX2_COMPILES}")
        # message(STATUS "AVX512 ${AVX512F_COMPILES}")
        #-----------------------------------------------
        # CONFIGURING CONFIG FLAG BASED ON PROGRAM RUNS
        #-----------------------------------------------
        if (AVX512EX_RUNS EQUAL 0)
            set(Config FALCON_ENABLE_AVX512EX)
        elseif (AVX512F_RUNS EQUAL 0)
            set(Config FALCON_ENABLE_AVX512F)
            #        elseif (AVX10_RUNS)
            #            set(Config FALCON_ENABLE_AVX10)
        elseif (AVX2_RUNS EQUAL 0)
            set(Config FALCON_ENABLE_AVX2)
        elseif (AVX_RUNS EQUAL 0)
            set(Config FALCON_ENABLE_AVX)
        elseif (SSE4_RUNS EQUAL 0)
            set(Config FALCON_ENABLE_SSE4)
        elseif (SSE2_RUNS EQUAL 0)
            set(Config FALCON_ENABLE_SSE2)
        elseif (NEON_RUNS EQUAL 0)
            set(Config FALCON_ENABLE_NEON)
        else ()
            set(Config FALCON_DISABLE_SIMD)
        endif ()
    endif ()

    #----------------------
    # SETUP COMPILER FLAGS
    #----------------------
    if (Config STREQUAL "FALCON_ENABLE_AVX512EX")
        set(MSVCCompilerFlag "/arch:AVX512")
        set(CompilerFlag "-mavx512f;-mavx512cd;-mavx512bw;-mavx512dq;-mavx512vl")
        message(STATUS "Turned on AVX512BW/DQ/VL")
    elseif (Config STREQUAL "FALCON_ENABLE_AVX512F")
        set(MSVCCompilerFlag "/arch:AVX512")
        set(CompilerFlag "-mavx512f")
        message(STATUS "Turned on AVX512F")
    elseif (Config STREQUAL "FALCON_ENABLE_AVX10")
        set(MSVCCompilerFlag "/arch:AVX10.1")
        set(CompilerFlag "-mavx10.1")
        message(STATUS "Turned on AVX10")
    elseif (Config STREQUAL "FALCON_ENABLE_AVX2")
        set(MSVCCompilerFlag "/arch:AVX2")
        set(CompilerFlag "-mavx2")
        message(STATUS "Turned on AVX2")
    elseif (Config STREQUAL "FALCON_ENABLE_AVX")
        set(MSVCCompilerFlag "/arch:AVX")
        set(CompilerFlag "-mavx")
        message(STATUS "Turned on AVX")
    elseif (Config STREQUAL "FALCON_ENABLE_SSE4")
        check_cxx_compiler_flag("/arch:SSE4.2" COMPILER_SUPPORTS_SSE4)
        if (COMPILER_SUPPORTS_SSE4)
            list(APPEND CompilerFlags "/arch:SSE4.2")
        else ()
            list(APPEND CompilerFlags "/arch:AVX")
        endif ()
        set(CompilerFlag "-msse4.2")
        message(STATUS "Turned on SSE4.2")
    elseif (Config STREQUAL "FALCON_ENABLE_SSE2")
        set(MSVCCompilerFlag "/arch:SSE2")
        set(CompilerFlag "-msse2")
        message(STATUS "Turned on SSE2")
    elseif (Config STREQUAL "FALCON_ENABLE_NEON")
        # AARCH64 comes with Neon Mandatory so need to switch flags
        message(STATUS "Turned on ARM Neon")
    elseif (Config STREQUAL "FALCON_DISABLE_SIMD")
        message(STATUS "SIMD is disabled.")
    else ()
        message(WARNING "Unsupported SIMD Flag. Refer docs for supported flags, or use 'AUTO' for automatically detecting based on system.")
        return() # Returning so that the flag will not get added!
    endif ()


    #----------------------
    # FMA SUPPORT CHECK
    #----------------------
    if (NOT Config STREQUAL FALCON_DISABLE_SIMD)
        # Check compiler flag support
        check_cxx_compiler_flag("-mfma" FMA3_FLAG_SUPPORTED)
        check_cxx_compiler_flag("-mfma4" FMA4_FLAG_SUPPORTED)
        check_cxx_compiler_flag("-march=native" ARCH_NATIVE_FLAG_SUPPORTED)

        if (FALCON_SIMD_FMA STREQUAL "AUTO")
            if (MSVC AND NOT (Config STREQUAL "FALCON_DISABLE_SIMD" OR Config STREQUAL "FALCON_ENABLE_SSE2" OR Config STREQUAL "FALCON_ENABLE_SSE4" OR Config STREQUAL "FALCON_ENABLE_AVX"))
                set(TEST_FLAG_FMA "/arch:AVX2")
            else ()
                # GCC / Clang / AppleClang
                if (FMA3_FLAG_SUPPORTED)
                    set(TEST_FLAG_FMA "-mavx;-march=native")
                elseif (FMA4_FLAG_SUPPORTED)
                    set(TEST_FLAG_FMA "-mavx;-march=native")
                elseif (ARCH_NATIVE_FLAG_SUPPORTED)
                    set(TEST_FLAG_FMA "-mavx;-march=native")
                else ()
                    message(STATUS "Compiler doesn't support FMA flags. FMA disabled.")
                endif ()
            endif ()

            if (TEST_FLAG_FMA)
                message(STATUS "Running FMA Extension Tests")
                try_run(
                        FMA_RUNS
                        FMA_COMPILES
                        ${TEST_COMPILE_DIR}
                        "${TEST_PROG_DIR}/FMATest.cpp"
                        CMAKE_FLAGS
                        "-DCMAKE_CXX_STANDARD=17"
                        "-DCMAKE_CXX_FLAGS=${TEST_FLAG_FMA}"
                        COMPILE_DEFINITIONS ${TEST_FLAG_FMA}
                )
                # Turn appropriate FMA Flags if supported
                if (FMA_RUNS EQUAL 0)
                    message(STATUS "FMA detection success!")
                else ()
                    message(STATUS "FMA detection failed!")
                endif ()
                if (FMA_RUNS EQUAL 0)
                    set(FMA_Config FALCON_ENABLE_FMA)
                endif ()
            endif ()
        endif ()

        # Manual FMA enabling
        if (FALCON_SIMD_FMA STREQUAL "ENABLED")
            if (ARCH_NATIVE_FLAG_SUPPORTED)
                set(FMA_Config FALCON_ENABLE_FMA)
            else ()
                message("FMA disabled due to lack of `-march` flag support. Try FMA3 or FMA4 option")
            endif ()
        elseif (FALCON_SIMD_FMA STREQUAL "FMA3")
            set(FMA_Config FALCON_ENABLE_FMA3)
        elseif (FALCON_SIMD_FMA STREQUAL "FMA4")
            set(FMA_Config FALCON_ENABLE_FMA4)
        endif ()

        # Set FMA Compiler flags
        if (FMA_Config STREQUAL FALCON_ENABLE_FMA)
            # string(APPEND CompilerFlag ";-march=native")
            # NOTE: The above code gives invalid combination error in CI/CD
            string(APPEND CompilerFlag ";-mfma")
        elseif (FMA_Config STREQUAL FALCON_ENABLE_FMA3)
            string(APPEND CompilerFlag ";-mfma")
        elseif (FMA_Config STREQUAL FALCON_ENABLE_FMA4)
            string(APPEND CompilerFlag ";-mfma4")
        endif ()
    else ()
        message(STATUS "FMA disabled since SIMD was disabled")
    endif ()


    #-------------------------
    # INJECT FLAGS AND MACROS
    #-------------------------
    if (MSVC)
        target_compile_options(${Target} ${Visibility} ${MSVCCompilerFlag})
    else ()
        target_compile_options(${Target} ${Visibility} ${CompilerFlag})
    endif ()
    target_compile_definitions(${Target} ${Visibility} ${Config} ${FMA_Config})

endfunction()