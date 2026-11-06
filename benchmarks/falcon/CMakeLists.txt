add_executable(FalconBenchmark)
set_target_properties(FalconBenchmark PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconBenchmark PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconBenchmark PROPERTIES CXX_EXTENSIONS OFF)

target_sources(FalconBenchmark PRIVATE
        SampleBenchmark.cpp
)

target_precompile_headers(
        FalconBenchmark
        PRIVATE
        <benchmark/benchmark.h>
)

target_link_libraries(
        FalconBenchmark
        PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
        Falcon::Falcon

        ${PROJECT_NAME}-StrictWarnings
        ${PROJECT_NAME}-ProjectSanitizers
)
