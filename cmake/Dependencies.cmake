include_guard()

include(FetchContent)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) # Statically link Gtest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark testing" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Disable benchmark install" FORCE)

set(VENDORS_DIR "Vendors")

# Google Test
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 # release-1.17.0
        SYSTEM
)

FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.5
        SYSTEM
)

# Test Harness Dependencies
if (FALCON_TESTS OR FALCON_SIMD_TESTS)
    FetchContent_MakeAvailable(googletest)
    # Group google_test projects into a "Gtest" folder
    set_target_properties(
            gtest gtest_main gmock gmock_main
            PROPERTIES FOLDER "${VENDORS_DIR}/Google/GTest"
    )

    if (MSVC)
        target_compile_options(gtest PRIVATE /WX- /W0)
        target_compile_options(gtest_main PRIVATE /WX- /W0)
    endif ()
endif ()


# Benchmark Dependencies
if (FALCON_BENCHMARK)
    FetchContent_MakeAvailable(googlebenchmark)
    if(MSVC)
    else()
        target_compile_options(benchmark PRIVATE -Wno-format-nonliteral)
        target_compile_options(benchmark_main PRIVATE -Wno-format-nonliteral)
    endif()
    set_target_properties(benchmark benchmark_main PROPERTIES FOLDER "${VENDORS_DIR}/Google/Benchmark")
endif ()
