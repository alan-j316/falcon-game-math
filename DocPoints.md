# Constraints and Design

**NOTE: Replace this document with a architecture document, and use this only as a scratchpad for quickly jolting down
choices.**

- Constant Vectors have a higher freedom with function like normalize, project, reject etc. allowing for cross-type as
  well as integral support.
- SIMD Vectors (Vec<n>) operations are limited to constant time operations.
- SIMD vector doesn't expose a ptr or operator*(unary) for getting a pointer to the internal memory, instead it provides
  a store function, which needs to be populated by a user provided buffer.
- Alternatively, we can convert the SIMD Vector to a Const Vector by using toCVec<n> but it must be stored and not used
  a temporary.
- SquareRoot for SIMD returns zero for integral negatives; floating points follow the standard, return NaN. 