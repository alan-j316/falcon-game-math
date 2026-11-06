# TODO LIST

## Matrices

- Add benchmarking to determine whether |(Bitwise OR) or ||(Logical OR) provides better performance in branching(used in
  safeDiv, and other similar functions)

## Vectors

- Add assert to div, normalize
- Update / to return Vector\*\*<Magnitude<T>>
- Add MSVC compiler check in equality to separate NaN evaluation during compile time

## Add SIMD Static Dispatch

## Playground
- World space projection
- More performant loader(OBJ/GLTF(External))
- Texture Mapping
- Lighting

## Utils

- Manhattan Distance(vector)
- Euclidean Distance(vector)
- Chebyshev Distance(vector)


## General Completion List
- SIMD Dispatch(Static + DLL Dispatch)
- Geometric Primitives(Line, Plane, AABB, etc)
- Transformation Factories(2d, 3d)
- Quaternions
- Transform3x4
- Transform4x3
- Transform3x2
- Transform2x3
- Faster OBJ Loader
- Rasterizer with Texture mapping
- Add asserts to functions that can have UB(like div by zero in vectors)
- Custom Trigonometric functions for constexpr evaluations
- Use FALCON_LEFT_HANDED where ever calculation are not coordinate system agnostic
- Wrapper for min, max, etc.
- Custom Sqrt Function for constexpr evaluations