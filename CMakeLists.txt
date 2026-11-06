cmake_minimum_required(VERSION 3.25)

project(FalconGameMath LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

add_library(${PROJECT_NAME}-StrictWarnings INTERFACE)
add_library(${PROJECT_NAME}-ProjectSanitizers INTERFACE)

set(DevToolsDir "Dev Tools")

# Turn on solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
option(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Custom Options
# Flags for keeping the library lightweight when a consumer imports it
option(FALCON_BENCHMARK "Enables FALCON Benchmark Suite")
option(FALCON_TESTS "Enables FALCON Benchmark Suite")
option(FALCON_DOCS "Enables FALCON Documentation Generation")
option(FALCON_STRICT_MODE "Enable Strict Warnings" OFF) # Option to enable compiler specific "Warning as Error"
option(FALCON_ASAN "Enable ASan" OFF) # Option to enable ASAN # TODO: Fix ASAN

include(cmake/ClangFormat.cmake)
include(cmake/ClangTidy.cmake)
include(cmake/Dependencies.cmake)
include(cmake/SimdCheck.cmake)

if (FALCON_DOCS)
    include(cmake/Doxygen.cmake)
endif ()

if (FALCON_STRICT_MODE)
    include(cmake/StrictMode.cmake)
endif ()

if (FALCON_ASAN)
    include(cmake/ASan.cmake)
endif ()

# Multi-processor compilation
if (MSVC AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "[Falcon]: Enabling Multiprocessor compilation on MSVC")
    add_compile_options("/MP")
endif ()

# Core Library
add_subdirectory(include)
# Test enabling is handled in tests CML per project
add_subdirectory(tests)

if (FALCON_BENCHMARK)
    message(STATUS "[Falcon]: Benchmarks are enabled")
    add_subdirectory(benchmarks)
endif ()