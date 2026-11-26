[![Unit Tests](https://github.com/alanabrahampkochumon-zqict/falcon-game-math/actions/workflows/unit-tests.yml/badge.svg)](https://github.com/alanabrahampkochumon-zqict/falcon-game-math/actions/workflows/unit-tests.yml)
[![Vectorization(SIMD) Tests](https://github.com/alan-j316/falcon-game-math/actions/workflows/vectorization-tests.yml/badge.svg)](https://github.com/alan-j316/falcon-game-math/actions/workflows/vectorization-tests.yml)

# Falcon Game Math

Modern High Performance Game Math library with SIMD acceleration on supported platforms.

_Requires C++20 or above_

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

Backed by a rigorous, TDD-driven test infrastructure featuring over 23,000 assertions across multiple compiled binaries
to guarantee deterministic mathematical precision and hardware reliability.

- **FALCON_BENCHMARK**: Enables FALCON Benchmark Suite (_Unused_).
- **FALCON_TESTS**: Enable FALCON Unit Tests.
- **NONCOMPREHENSIVE**: Run unit tests with essential type matrix only.

### SIMD

Hardware SIMD instruction sets are controlled globally via the FALCON_SIMD_MODE CMake variable. Set this variable to
configure the target architecture for the library and its consumers.

- **AUTO**: Automatically detect SIMD based on the host machine.
- **FALCON_ENABLE_AVX512EX**: Enables AVX512EX support (EX require all AVX512 extensions like BW/VL...).
- **FALCON_ENABLE_AVX512F**: Enables AVX512F support.
- **FALCON_ENABLE_AVX10**: Enables AVX10.1 support. *No auto-detect available*
- **FALCON_ENABLE_AVX2**: Enables AVX2 support.
- **FALCON_ENABLE_AVX**: Enables AVX support.
- **FALCON_ENABLE_SSE4**: Enables SSE4 support.
- **FALCON_ENABLE_SSE2**: Enables SSE2 support.
- **FALCON_ENABLE_NEON**: Enables Neon support (Not supported yet!).
- **FALCON_DISABLE_SIMD**: Disables SIMD (Not supported yet!).

## How to install (CMake FetchContent)

1. Use `FetchContent` to pull the library.

```cmake
    FetchContent_Declare(
        falcon
        GIT_REPOSITORY https://github.com/alan-j316/falcon-game-math.git
        GIT_TAG 538f41eeeda7f1d2e61f21c06ea118b7a98b4ddd
        SYSTEM
)
```

2. Link with your target.
    ```cmake
        add_executable(SampleGame)
        target_link_libraries(SampleGame PRIVATE Falcon::Falcon)    
   ```

### Usage

```c++
    flcn::Vec4F position{1, 2, 3, 1};
    flcn::Mat4F scale = flcn::Mat4F::makeScale(1.2);
    const auto scaled = scale * position;

    // Simd Accelerated types.
    flcn::simd::Vec2F posXY{1, 2};
    
    // Simd Types
    flcn::Simd128<float, 4> simd1{1, 2, 3, 4}, simd2{4, 5, 6, 7};
    const auto res = simd1 + simd2;
```

### Limitation and Future Expansion

Currently, supports foundational primitives (Vec2-4, Mat2-4). Advanced operations like packing, unpacking, and
perspective projections are planned for upcoming iterations. Hardware SIMD abstractions (SSE2, AVX, AVX2) are available,
with functional support expanding as needed.

### Immediate expansion

- [x] Simd128 scalar
- [x] Simd256 scalar
- [ ] Matrix Projection and Translation Factories
- [ ] Vec4, Mat2, 3, 4 refactor to Simd
- [ ] Packing and Unpacking
- [ ] Quaternion
- [ ] std::hash support

### Future Development

- [ ] Simd512
- [ ] Neon Support
- [ ] Dual Quaternions
- [ ] Geometric Primitives including lines, planes, etc
- [ ] Constexpr variants of Trigonometric and math functions.
- [ ] Collision Primitives

_Note: This roadmap is non-exhaustive and the order of development is subject to change._

### Project Samples

- [Tempest: Vulkan-based Game Engine](https://github.com/alan-j316/tempest)
- [Ephemeral: Vulkan-based API decoupled renderer](https://github.com/alan-j316/ephemeral)
- [Colloid: Software Rasterizer w/ SIMD acceleration](https://github.com/alan-j316/colloid)

----

#### References

- <a href="https://foundationsofgameenginedev.com/" target="_blank">Eric Lengyel's Foundations of Game Engine
  Development Series</a>
- <a href="https://gamemath.com/" target="_blank">3D Math Primer for Graphics and Game Engine Development</a>
