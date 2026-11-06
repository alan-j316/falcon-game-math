[![Unit Tests](https://github.com/alanabrahampkochumon-zqict/falcon-game-math/actions/workflows/unit-tests.yml/badge.svg)](https://github.com/alanabrahampkochumon-zqict/falcon-game-math/actions/workflows/unit-tests.yml)

# Falcon Game Math

Modern High Performance Game Math library with SIMD acceleration on supported platforms.

*Requires C++20 or above*

## Requirements

* <a href="https://cmake.org/download/" target="_blank">CMake 3.26</a> or above
* <a href="https://cmake.org/download/" target="_blank">Git</a>

## CMake Options

### General

- **FALCON_DOCS**: Enables FALCON Documentation Generation.
- **FALCON_STRICT_MODE**: Enables Strict Warnings, treating warnings as errors.
- **FALCON_ASAN**: Enables Address Sanitizer in Strict Mode.
- **FALCON_FORCE_LEFT_HANDED**: Switches Library to use Left Handed Coordinate System (Right-Handed by default).

### Testing and Benchmarks

- **FALCON_BENCHMARK**: Enables FALCON Benchmark Suite.
- **FALCON_TESTS**: Enable FALCON Unit Tests.
- **NONCOMPREHENSIVE**: Run unit tests with essential type matrix only.

### SIMD

The flag is currently only available for testing targets and will need to be defined per target using the
`AddSimdCompilerFlag` CMake function.

- **AUTO**: Automatically detect SIMD based on the host machine.
- **FALCON_ENABLE_AVX512**: Enables AVX512 support.
- **FALCON_ENABLE_AVX10**: Enables AVX10.1 support. *No auto-detect available*
- **FALCON_ENABLE_AVX2**: Enables AVX2 support.
- **FALCON_ENABLE_AVX**: Enables AVX support.
- **FALCON_ENABLE_SSE4**: Enables SSE4 support.
- **FALCON_ENABLE_SSE2**: Enables SSE2 support.
- **FALCON_DISABLE_SIMD**: Disables SIMD.

## How to install (CMake FetchContent)

1. Use `FetchContent` to pull the library.

```cmake
    FetchContent_Declare(
        falcon
        GIT_REPOSITORY https://github.com/alanabrahampkochumon-zqict/falcon-game-math.git
        GIT_TAG 538f41eeeda7f1d2e61f21c06ea118b7a98b4ddd
        SYSTEM
)
```

2. Link with your target.
    ```cmake
        add_executable(SampleGame)
        target_link_libraries(SampleGame PRIVATE Falcon::Falcon)    
   ```

## References

- <a href="https://foundationsofgameenginedev.com/" target="_blank">Eric Lengyel's Foundations of Game Engine
  Development Series</a>
- <a href="https://gamemath.com/" target="_blank">3D Math Primer for Graphics and Game Engine Development</a>
