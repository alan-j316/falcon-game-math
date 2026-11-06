#pragma once
/**
 * @file Vec2.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 15, 2026
 *
 * @brief High-performance 2D vector implementation with SIMD acceleration.
 *
 * @note Arithmetic operations are limited to numeric types via `StrictArithmetic` concept.
 * @warning Due to the inherent nature of SIMD, indexing using operator[] is strongly discouraged.
 *          For non-frequent indices use functional variants like x(), y(), s(), t(), etc.
 *          or compile-time indexing using get<Index> or set<Index>.
 *          If your program require frequent mutation of types, it is recommended to use @ref flcn::CVec2
 *          and convert it to Vec2 after mutation logic, prior to operations.
 *
 * @par Configuration
 * Define `ENABLE_FALCON_SHADER_OPERATORS` to enable comparison operators (>, <, etc.).
 * Even if disabled, functional comparisons like `greaterThan()` remain available.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

// TODO: Update header description
#include "falcon/math/common/Config.h"
#include "falcon/math/common/Constants.h"
#include "falcon/math/common/MathTraits.h"
#include "falcon/math/common/OperationStatus.h"
#include "falcon/math/common/Types.h"

#include <falcon/core/Preprocessors.h>
#include <falcon/core/traits/TypeHelpers.h>
#include <falcon/simd/FalconSimd.h>
#include <iomanip>
#include <type_traits>


namespace flcn
{
    using namespace flcn::types;
    using namespace flcn::constants;

    template <typename T>
    using Mask_t = UInt_t<T>;

    template <Arithmetic T>
    struct alignas(16) Vec2
    {
    private:
        /// ForwardDeclarations
        template <size_t Index>
        class ConstIndexableProxy;
        class IndexableProxy;


    public:
        /**
         * @addtogroup FALCON_Vec2_Members
         * @{
         */

        using value_type = T; ///< The numeric type of the vector components.

        static constexpr size_t DIMENSION = 2; ///< The number of components of the vector.

        /** @} */


        /**
         * @addtogroup FALCON_Vec2_Init
         * @{
         */

        /**
         * @brief Initialize an uninitialized @ref Vec2 instance.
         *
         * @warning The components are left uninitialized (containing garbage data)
         *          to maximize SIMD optimization and maintain triviality.
         *
         * @note Use value-initialization (`{}`) or the static helper
         *       @ref flcn::Vec2<T>::zero() to guarantee a zeroed vector.
         */
        Vec2() = default;


        /**
         * @brief Initialize @ref Vec2 with a single value broadcast across its components.
         *
         * @param[in] val The value to use broadcast across all vector components.
         */
        [[nodiscard]] explicit constexpr Vec2(T val) noexcept;


        /**
         * @brief Initialize @ref Vec2 with passed in values.
         *
         * @param[in] v1 The first entry of @ref Vec2.
         * @param[in] v2 The second entry of @ref Vec2.
         */
        [[nodiscard]] constexpr Vec2(T v1, T v2) noexcept;


        /**
         * @brief Initialize @ref Vec2 from another @ref Vec2 of a different type.
         *
         * @tparam U Numeric type of the source vector.
         *
         * @param[in] other The source vector to be converted.
         */
        template <Arithmetic U>
        [[nodiscard]] explicit constexpr Vec2(const Vec2<U>& other) noexcept;


        /**
         * @brief Initialize a @ref Vec2 with an Simd128_t register.
         * @param reg The register to bind to this vector.
         */
        [[nodiscard]] explicit constexpr Vec2(const flcn::Simd128_t<T, DIMENSION>& reg) noexcept;


        /// @brief Convert this Vec2 to CVec2.
        /// @note Use this minimally, as these can add unnecessary overheads.
        [[nodiscard]] constexpr CVec2<T> toCVec2() const noexcept;


        /// @brief Convert @p vec to a CVec2.
        /// @note Use this minimally, as these can add unnecessary overheads.
        [[nodiscard]] static constexpr CVec2<T> toCVec2(const Vec2& vec) noexcept;

        /** @} */


        /**
         * @addtogroup FALCON_Vec2_Access
         * @{
         */

        /**
         * @brief Access the element at the first location.
         * @return A copy of the first vector element.
         */
        [[nodiscard]] constexpr T x() const noexcept;


        /**
         * @brief Access the element at the first location (read-write access).
         * @return A reference to the first element of the vector.
         */
        [[nodiscard]] constexpr ConstIndexableProxy<0> x() noexcept;


        /**
         * @brief Access the element at the last location.
         * @return A copy of the last vector element.
         */
        [[nodiscard]] constexpr T y() const noexcept;


        /**
         * @brief Access the element at the last location (read-write access).
         * @return A reference to the last element of the vector.
         */
        [[nodiscard]] constexpr ConstIndexableProxy<1> y() noexcept;


        /**
         * @brief Access the element at the first location.
         * @return A copy of the first vector element.
         */
        [[nodiscard]] constexpr T s() const noexcept;


        /**
         * @brief Access the element at the first location (read-write access).
         * @return A reference to the first element of the vector.
         */
        [[nodiscard]] constexpr ConstIndexableProxy<0> s() noexcept;


        /**
         * @brief Access the element at the last location.
         * @return A copy of the last vector element.
         */
        [[nodiscard]] constexpr T t() const noexcept;


        /**
         * @brief Access the element at the last location (read-write access).
         * @return A reference to the last element of the vector.
         */
        [[nodiscard]] constexpr ConstIndexableProxy<1> t() noexcept;


        /**
         * @brief Access the element at the first location.
         * @return A copy of the first vector element.
         */
        [[nodiscard]] constexpr T r() const noexcept;


        /**
         * @brief Access the element at the first location (read-write access).
         * @return A reference to the first element of the vector.
         */
        [[nodiscard]] constexpr ConstIndexableProxy<0> r() noexcept;


        /**
         * @brief Access the element at the last location.
         * @return A copy of the last vector element.
         */
        [[nodiscard]] constexpr T g() const noexcept;


        /**
         * @brief Access the element at the last location (read-write access).
         * @return A reference to the last element of the vector.
         */
        [[nodiscard]] constexpr ConstIndexableProxy<1> g() noexcept;


        /**
         * @brief Access the element at the specified location.
         *        Provide read-write access to the element.
         *
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @param[in] idx The index of the vector component.
         *
         * @return A reference to the vector component(Proxy).
         */
        constexpr IndexableProxy operator[](size_t idx) noexcept;


        /**
         * @brief Access the element at the specified location.
         *
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @warning Runtime indexing is an expensive SIMD operation. If you have a lot of indexing calls
         *          use @ref CVec2 and convert it to @ref Vec2 when it is time to perform operations.
         *
         *
         * @param[in] idx The index of the vector component.
         *
         * @return A copy of the vector component.
         */
        constexpr T operator[](size_t idx) const noexcept;


        /// @brief Get the element at @p Index.
        template <size_t Index>
        constexpr T get() const noexcept;


        /// @brief Get the element at @p Index (non-const variant).
        template <size_t Index>
        constexpr T get() noexcept;


        /// @brief Get the element at @p Index to @p value.
        template <size_t Index>
        constexpr void set(T value) noexcept;

        /** @} */



        /**
         * @addtogroup FALCON_Vec2_Swizzle
         * @{
         */

        /**
         * @brief Construct a new vector by rearranging, duplicating, or isolating components of this vector.
         *
         * @note Bounds checking for the provided indices is strictly enforced at compile-time.
         *       Providing an out-of-bounds index will result in a compilation error, guaranteeing zero
         *       runtime overhead.
         *
         * @tparam Indices The component indices used to construct the new vector.
         *                 See @ref flcn::axis, @ref flcn::colors, and @ref flcn::stp for available swizzle aliases.
         *
         * @return A new vector containing the requested components or the component if @p Indices is 1.
         *         The dimension of the returned vector perfectly matches the number of indices provided.
         */
        template <size_t... Indices>
        [[nodiscard("Swizzling returns a new vector and does not mutate the original.")]]
        constexpr auto swizzle() const noexcept;


        /**
         * @brief Construct a new vector by rearranging, duplicating, or isolating components of @p Vec.
         *
         * @note Bounds checking for the provided indices is strictly enforced at compile-time.
         *       Providing an out-of-bounds index will result in a compilation error, guaranteeing zero
         *       runtime overhead.
         *
         * @tparam Indices The component indices used to construct the new vector.
         *                 See @ref flcn::axis, @ref flcn::colors, and @ref flcn::stp for available swizzle aliases.
         *
         * @param vec The vector to shuffle, rearrange or isolate components.
         *
         * @return A new vector containing the requested components or the component if @p Indices is 1.
         *         The dimension of the returned vector perfectly matches the number of indices provided.
         */
        template <size_t... Indices>
        [[nodiscard("Swizzling returns a new vector and does not mutate the original.")]]
        static constexpr auto swizzle(const Vec2& vec) noexcept;

        /** @} */

        /**
         * @addtogroup FALCON_CVec2_Ptr
         * @{
         */

        /**
         * @brief Store the values of this vector to @p pBuffer.
         * @note  Since we cannot return a pointer to a buffer, due to lifetime limitation
         *        of pointer allocated on the callstack of @ref store,
         *        use either @ref store or storeUnaligned.
         *        Alternatively, convert to a CVec2 using @ref toCVec2 and then use *cvec or cvec.ptr().
         *        *But you shouldn't make the CVec2 instance a temporary.*
         * @note The buffer must be of an adequate size to store the contents.
         *
         * @warning @p pBuffer must be aligned to 16-byte boundary.
         *          If you want to store unaligned memory use @ref storeUnaligned.
         *
         * @code
         * // DO
         * auto cvec2 = vec2.toCVec2();
         * auto ptr = *cvec2();
         *
         * // OR
         * alignas(16) float data[2];
         * vec2.store(data);
         *
         * // DON'T
         * auto ptr = *(vec2.toCVec2());
         * @endcode
         *
         * @relatedalso store(Vec2<T>, T*)
         * @relatedalso storeUnaligned(T*)
         * @relatedalso storeUnaligned(Vec2<T>, T*)
         */
        constexpr void store(T* pBuffer) const noexcept;


        /**
         * @brief Store the values of @p vec to @p pBuffer.
         * @note  Since we cannot return a pointer to a buffer, due to lifetime limitation
         *        of pointer allocated on the callstack of @ref store,
         *        use either @ref store or storeUnaligned.
         *        Alternatively, convert to a CVec2 using @ref toCVec2 and then use *cvec or cvec.ptr().
         *        *But you shouldn't make the CVec2 instance a temporary.*
         * @note The buffer must be of an adequate size to store the contents.
         *
         * @warning @p pBuffer must be aligned to 16-byte boundary.
         *          If you want to store unaligned memory use @ref storeUnaligned.
         *
         * @code
         * // DO
         * auto cvec2 = vec2.toCVec2();
         * auto ptr = *cvec2();
         *
         * // OR
         * alignas(16) float data[2];
         * vec2.store(data);
         *
         * // DON'T
         * auto ptr = *(vec2.toCVec2());
         * @endcode
         *
         * @relatedalso store(T*)
         * @relatedalso storeUnaligned(T*)
         * @relatedalso storeUnaligned(Vec2<T>, T*)
         */
        static constexpr void store(const Vec2& vec, T* pBuffer) noexcept;


        /**
         * @brief Store the values of this vector to @p pBuffer.
         * @note  Since we cannot return a pointer to a buffer, due to lifetime limitation
         *        of pointer allocated on the callstack of @ref storeUnaligned,
         *        use either @ref store or storeUnaligned.
         *        Alternatively, convert to a CVec2 using @ref toCVec2 and then use *cvec or cvec.ptr().
         *        *But you shouldn't make the CVec2 instance a temporary.*
         * @note The buffer must be of an adequate size to store the contents.
         *
         * @warning No memory alignment necessary.
         *
         * @code
         * // DO
         * auto cvec2 = vec2.toCVec2();
         * auto ptr = *cvec2();
         *
         * // OR
         * float data[2];
         * vec2.store(data);
         *
         * // DON'T
         * auto ptr = *(vec2.toCVec2());
         * @endcode
         *
         * @relatedalso store(T*)
         * @relatedalso store(Vec2<T>, T*)
         * @relatedalso storeUnaligned(Vec2<T>, T*)
         */
        constexpr void storeUnaligned(T* pBuffer) const noexcept;


        /**
         * @brief Store the values of @p vec to @p pBuffer.
         * @note  Since we cannot return a pointer to a buffer, due to lifetime limitation
         *        of pointer allocated on the callstack of @ref storeUnaligned,
         *        use either @ref store or storeUnaligned.
         *        Alternatively, convert to a CVec2 using @ref toCVec2 and then use *cvec or cvec.ptr().
         *        *But you shouldn't make the CVec2 instance a temporary.*
         * @note The buffer must be of an adequate size to store the contents.
         *
         * @warning No memory alignment necessary.
         *
         * @code
         * // DO
         * auto cvec2 = vec2.toCVec2();
         * auto ptr = *cvec2();
         *
         * // OR
         * float data[2];
         * vec2.storeUnaligned(data);
         *
         * // DON'T
         * auto ptr = *(vec2.toCVec2());
         * @endcode
         *
         * @relatedalso store(T*)
         * @relatedalso store(Vec2<T>, T*)
         * @relatedalso storeUnaligned(T*)
         */
        static constexpr void storeUnaligned(const Vec2& vec, T* pBuffer) noexcept;

        /** @} */


        /**
         * @addtogroup FALCON_Vec2_Equality
         * @{
         */

        /**
         * @brief Compare all components of this vector with @p rhs vector for equality.
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @param[in] rhs     The vector to compare against.
         *
         * @return True if all components are equal.
         */
        [[nodiscard]] constexpr bool allEq(const Vec2& rhs) const noexcept;


        /**
         * @brief Compare all components of @p lhs vector with @p rhs vector for equality.
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         *
         * @return `true` if all components are equal.
         */
        [[nodiscard]] static constexpr bool allEq(const Vec2& lhs, const Vec2& rhs) noexcept;


        /**
         * @brief Compare all components of this vector with @p rhs vector for inequality.
         *
         * @note To obtain a component-wise boolean mask, use @ref neq.
         *
         *
         * @param[in] rhs     The vector to compare against.
         *
         * @return `true` if any of the components are not equal.
         */
        [[nodiscard]] constexpr bool anyNeq(const Vec2& rhs) const noexcept;


        /**
         * @brief Compare all components of @p lhs vector with @p rhs vector for inequality.
         *
         * @note To obtain a component-wise boolean mask, use @ref neq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         *
         * @return `true` if any of the components are not equal.
         */
        [[nodiscard]] static constexpr bool anyNeq(const Vec2& lhs, const Vec2& rhs) noexcept;


        /**
         * @copybrief allEq(const Vec2&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return True if all components are equivalent within the default epsilon.
         */
        [[nodiscard]] constexpr bool operator==(const Vec2& rhs) const noexcept;


        /**
         * @copybrief anyNeq(const Vec2&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return True if any of the components are not equivalent within the default epsilon.
         */
        [[nodiscard]] constexpr bool operator!=(const Vec2& rhs) const noexcept;


        /**
         * @brief Perform component-wise equality check between this vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note To obtain a single scalar result, use @ref allEq or @ref operator==.
         *
         * @param[in] rhs     The vector to compare against.
         *
         * @note Use @ref toBool to convert mask vector to a boolean vector.
         * @note For direct comparisons use @ref flcn::TrueMask<T> or flcn::FalseMask<T>.
         *
         * @return A @ref Mask_t(unsigned integral) Vec2 with `true` represented by 111...111 and `false` by 000...000.
         */
        [[nodiscard]] constexpr Vec2<Mask_t<T>> eq(const Vec2& rhs) const noexcept;


        /**
         * @brief Perform component-wise equality check between @p lhs and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         *
         * @note Use @ref toBool to convert mask vector to a boolean vector.
         * @note For direct comparisons use @ref flcn::TrueMask<T> or flcn::FalseMask<T>.
         *
         * @return A @ref Mask_t(unsigned integral) Vec2 with `true` represented by 111...111 and `false` by 000...000.
         */
        [[nodiscard]] static constexpr Vec2<Mask_t<T>> eq(const Vec2& lhs, const Vec2& rhs) noexcept;


        /**
         * @brief Perform component-wise inequality check between this vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note To obtain a single scalar result, use @ref anyNeq or @ref operator!=.
         *
         * @param[in] rhs     The vector to compare against.
         *
         * @note Use @ref toBool to convert mask vector to a boolean vector.
         * @note For direct comparisons use @ref flcn::TrueMask<T> or flcn::FalseMask<T>.
         *
         * @return A @ref Mask_t(unsigned integral) Vec2 with `true` represented by 111...111 and `false` by 000...000.
         */
        [[nodiscard]] constexpr Vec2<Mask_t<T>> neq(const Vec2& rhs) const noexcept;


        /**
         * @brief Perform component-wise inequality check between @p lhs vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         *
         * @note Use @ref toBool to convert mask vector to a boolean vector.
         * @note For direct comparisons use @ref flcn::TrueMask<T> or flcn::FalseMask<T>.
         *
         * @return A @ref Mask_t(unsigned integral) Vec2 with `true` represented by 111...111 and `false` by 000...000.
         */
        [[nodiscard]] static constexpr Vec2<Mask_t<T>> neq(const Vec2& lhs, const Vec2& rhs) noexcept;

        /** @} */

        // TODO: Add near equals
        // TODO: Add tests create conversion.
        [[nodiscard]] constexpr Vec2<bool> toBool() const noexcept
        { return Vec2<bool>(static_cast<bool>(x()), static_cast<bool>(y())); }

        /**
         * @addtogroup FALCON_Vec2_Comparison
         * @{
         */

        /**
         * @brief Perform component-wise greater-than comparison between this vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @note Use @ref toBool to convert mask vector to a boolean vector.
         * @note For direct comparisons use @ref flcn::TrueMask<T> or flcn::FalseMask<T>.
         *
         * @return A @ref Mask_t(unsigned integral) Vec2 with `true` represented by 111...111 and `false` by 000...000.
         */
        [[nodiscard]] constexpr Vec2<Mask_t<T>> gt(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater-than comparison between @p lhs vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @note Use @ref toBool to convert mask vector to a boolean vector.
         * @note For direct comparisons use @ref flcn::TrueMask<T> or flcn::FalseMask<T>.
         *
         * @return A @ref Mask_t(unsigned integral) Vec2 with `true` represented by 111...111 and `false` by 000...000.
         */
        [[nodiscard]] static constexpr Vec2<Mask_t<T>> gt(const Vec2& lhs, const Vec2& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater-than-or-equal comparison between this vector and @p rhs
         *        vector. Compare each component pair and returns a boolean mask.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @note Use @ref toBool to convert mask vector to a boolean vector.
         * @note For direct comparisons use @ref flcn::TrueMask<T> or flcn::FalseMask<T>.
         *
         * @return A @ref Mask_t(unsigned integral) Vec2 with `true` represented by 111...111 and `false` by 000...000.
         */
        [[nodiscard]] constexpr Vec2<Mask_t<T>> gte(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater-than-or-equal comparison between @p lhs vector and @p rhs
         *        vector. Compare each component pair and returns a boolean mask.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @note Use @ref toBool to convert mask vector to a boolean vector.
         * @note For direct comparisons use @ref flcn::TrueMask<T> or flcn::FalseMask<T>.
         *
         * @return A @ref Mask_t(unsigned integral) Vec2 with `true` represented by 111...111 and `false` by 000...000.
         */
        [[nodiscard]] static constexpr Vec2<Mask_t<T>> gte(const Vec2& lhs, const Vec2& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than comparison between this vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to
         *       compiler-level constant folding bugs.
         *       Runtime execution remains IEEE 754 compliant under /fp:strict.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @note Use @ref toBool to convert mask vector to a boolean vector.
         * @note For direct comparisons use @ref flcn::TrueMask<T> or flcn::FalseMask<T>.
         *
         * @return A @ref Mask_t(unsigned integral) Vec2 with `true` represented by 111...111 and `false` by 000...000.
         */
        [[nodiscard]] constexpr Vec2<Mask_t<T>> lt(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than comparison between @p lhs vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to
         *       compiler-level constant folding bugs.
         *       Runtime execution remains IEEE 754 compliant under /fp:strict.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @note Use @ref toBool to convert mask vector to a boolean vector.
         * @note For direct comparisons use @ref flcn::TrueMask<T> or flcn::FalseMask<T>.
         *
         * @return A @ref Mask_t(unsigned integral) Vec2 with `true` represented by 111...111 and `false` by 000...000.
         */
        [[nodiscard]] static constexpr Vec2<Mask_t<T>> lt(const Vec2& lhs, const Vec2& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than-or-equal comparison between this vector and @p rhs vector.
         *        Compares each component pair and returns a boolean mask.
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to
         *       compiler-level constant folding bugs.
         *       Runtime execution remains IEEE 754 compliant under /fp:strict.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @note Use @ref toBool to convert mask vector to a boolean vector.
         * @note For direct comparisons use @ref flcn::TrueMask<T> or flcn::FalseMask<T>.
         *
         * @return A @ref Mask_t(unsigned integral) Vec2 with `true` represented by 111...111 and `false` by 000...000.
         */
        [[nodiscard]] constexpr Vec2<Mask_t<T>> lte(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than-or-equal comparison between @p lhs vector and @p rhs
         *        vector. Compares each component pair and returns a boolean mask.
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to
         *       compiler-level constant folding bugs.
         *       Runtime execution remains IEEE 754 compliant under /fp:strict.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @note Use @ref toBool to convert mask vector to a boolean vector.
         * @note For direct comparisons use @ref flcn::TrueMask<T> or flcn::FalseMask<T>.
         *
         * @return A @ref Mask_t(unsigned integral) Vec2 with `true` represented by 111...111 and `false` by 000...000.
         */
        [[nodiscard]] static constexpr Vec2<Mask_t<T>> lte(const Vec2& lhs, const Vec2& rhs) noexcept
            requires StrictArithmetic<T>;


#ifdef ENABLE_FALCON_SHADER_OPERATORS

        /**
         * @copydoc gt(const Vec2&) const
         */
        [[nodiscard]] constexpr Vec2<Mask_t<T>> operator>(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc gte(const Vec2&) const
         */
        [[nodiscard]] constexpr Vec2<Mask_t<T>> operator>=(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc lt(const Vec2&) const
         */
        [[nodiscard]] constexpr Vec2<Mask_t<T>> operator<(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc lte(const Vec2&) const
         */
        [[nodiscard]] constexpr Vec2<Mask_t<T>> operator<=(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;
#endif

        /** @} */


        /**
         * @addtogroup FALCON_Vec2_Bitwise
         * @{
         */

        /**
         * @brief Perform component-wise logical AND between this vector and @p rhs vector.
         *        Compute the conjunction between each component pair.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A @ref Vec2<bool> mask containing the results of component-wise AND.
         */
        [[nodiscard]] constexpr Vec2 operator&(const Vec2& rhs) const noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform an in-place component-wise logical AND between this vector and @p rhs vector.
         *        Compute the conjunction between each component pair in-place and update the calling vector.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A reference to this vector (*this).
         */
        constexpr Vec2& operator&=(const Vec2& rhs) noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise logical OR between this vector and @p rhs vector.
         *        Compute the disjunction between each component pair.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A @ref Vec2<bool> mask containing the results of component-wise OR.
         */
        [[nodiscard]] constexpr Vec2 operator|(const Vec2& rhs) const noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform an in-place component-wise logical OR between this vector and @p rhs vector.
         *        Compute the disjunction between each component pair in-place and update the calling vector.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A reference to this vector (*this).
         */
        constexpr Vec2& operator|=(const Vec2& rhs) noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Apply a component-wise logical NOT on this vector.
         *        Invert each boolean component and returns a new @ref Vec2<bool>.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @return A @ref Vec2<bool> with inverted values.
         */
        [[nodiscard]] constexpr Vec2 operator!() const noexcept
            requires std::is_same_v<T, bool>;

        /** @} */


        /**
         * @addtogroup FALCON_Vec2_Arithmetic
         * @{
         */

        /**
         * @brief Compute the component-wise sum of this vector with @p rhs vector and return a new vector.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Both operands must be of the same numeric type.
         *
         * @param[in] rhs The vector to add.
         *
         * @return A new @ref Vec2 containing the component-wise sum.
         */
        [[nodiscard]] constexpr Vec2 operator+(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise sum of this vector with @p rhs vector in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *@note Both operands must be of the same numeric type.
         *
         * @param[in] rhs The vector to add.
         *
         * @return A reference to this vector (*this).
         */
        constexpr Vec2& operator+=(const Vec2& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise difference between this vector and @p rhs vector and return a
         *        new vector.
         *
         * @note Promotes the result to the wider type using @ref Vec2.
         * @note Both operands must be of the same numeric type.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to subtract.
         *
         * @return A new @ref Vec2 containing the component-wise difference.
         */
        [[nodiscard]] constexpr Vec2 operator-(const Vec2 rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise difference between this vector and @p rhs vector in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Both operands must be of the same numeric type.
         *
         * @param[in] rhs The vector to subtract.
         *
         * @return A reference to this vector (*this).
         */
        constexpr Vec2& operator-=(const Vec2& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Negate each component of this vector and return a new @ref Vec2<T>.
         *
         * @note Operation is restricted to numeric types via @ref SignedStrictArithmetic.
         *
         * @return A new @ref flcn::Vec2 with negated components.
         */
        [[nodiscard]] constexpr Vec2 operator-() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the component-wise product between this vector and @p scalar and
         *        return a new vector.
         *
         * @warning The scalar value will be cast to the numeric type of the vector.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Vec2 scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr Vec2 operator*(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise product between this vector and @p scalar in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @warning The scalar value will be cast to the numeric type of the vector.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic S>
        constexpr Vec2& operator*=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of this vector by @p scalar and return a new vector.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Performs assertion for division by zero in **Debug mode**.
         *
         * @warning The scalar value will be cast to the numeric type of the vector.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Vec2 scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr Vec2 operator/(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of this vector by @p scalar in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Performs assertion for division by zero in **Debug mode**.
         *
         * @warning The scalar value will be cast to the numeric type of the vector.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic S>
        constexpr Vec2& operator/=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of this vector by @p scalar and return a new vector.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN
         *       components, returns a zero vector.
         * @note Operation is restricted to numeric types via @ref flcn::StrictArithmetic.
         *
         * @warning The scalar value will be cast to the numeric type of the vector.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref flcn::StrictArithmetic.
         *
         * @param[in] scalar The value to divide the vector components by.
         *
         * @return A new @ref Vec2 resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors contains NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr Vec2 safeDiv(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of @p Vec by @p scalar and return a new vector.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN
         *       components, returns a zero vector.
         * @note Operation is restricted to numeric types via @ref flcn::StrictArithmetic.
         *
         * @warning The scalar value will be cast to the numeric type of the vector.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref flcn::StrictArithmetic.
         *
         * @param[in] vec The vector to divide.
         * @param[in] scalar The value to divide the vector components by.
         *
         * @return A new @ref Vec2 resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors contains NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr Vec2 safeDiv(const Vec2& vec, S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of this vector by @p scalar, return a new vector,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN
         *       components, returns a zero vector.
         * @note Operation is restricted to numeric types via @ref flcn::StrictArithmetic.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over
         *       mathematical invalidity (Division by Zero) when reporting status.
         *
         * @warning The scalar value will be cast to the numeric type of the vector.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref flcn::StrictArithmetic.
         *
         * @param[in] scalar  The value to divide the vector components by.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return A new @ref Vec2 resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors+ has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr Vec2 tryDiv(S scalar, OperationStatus& status) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of @p Vec by @p scalar, return a new vector,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN
         *       components, returns a zero vector.
         * @note Promotes the result to the wider type using @ref PromotedVec2<T, S>.
         * @note Operation is restricted to numeric types via @ref flcn::StrictArithmetic.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over
         *       mathematical invalidity (Division by Zero) when reporting status.
         *
         * @warning The scalar value will be cast to the numeric type of the vector.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref flcn::StrictArithmetic.
         *
         * @param[in] vec     The vector to divide.
         * @param[in] scalar  The value to divide the vector components by.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return A new @ref Vec2 resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors+ has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr Vec2 tryDiv(const Vec2& vec, S scalar, OperationStatus& status) noexcept
            requires StrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FALCON_Vec2_Product
         * @{
         */

        /**
         * @brief Compute the dot product with another vector.
         *        \f$ \mathbf{a} \cdot \mathbf{b} = \sum_{i=1}^{2} a_i b_i \f$
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compute the dot product with.
         *
         * @return The scalar dot product of the two vectors.
         */
        [[nodiscard]] constexpr T dot(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the dot product of two vectors.
         *        \f$ \mathbf{a} \cdot \mathbf{b} = \sum_{i=1}^{2} a_i b_i \f$
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @param[in] lhs The first vector to compute the dot product with.
         * @param[in] rhs The second vector to compute the dot product with.
         *
         * @return The scalar dot product of @p lhs and @p rhs.
         */
        [[nodiscard]] static constexpr T dot(const Vec2& lhs, const Vec2& rhs) noexcept
            requires StrictArithmetic<T>;


        //         /**
        //          * @brief Compute the tensor product with another vector.
        //          *        \f$ \mathbf{u} \otimes \mathbf{v} = u v^\top \f$
        //          *
        //          * @note Promotes the result to the wider type using @ref PromotedMat2<T, U>.
        //          * @note Operation is restricted to numeric types via @ref StrictArithmetic.
        //          *
        //          * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
        //          *
        //          * @param[in] rhs The vector to compute the tensor product with.
        //          *
        //          * @return A new 2D matrix containing the tensor product.
        //          */
        //         template <StrictArithmetic U>
        //             requires StrictSignedness<T, U>
        //         [[nodiscard]] constexpr PromotedMat2<T, U> tensorProduct(const Vec2& rhs) const noexcept
        //             requires StrictArithmetic<T>;
        //
        //
        //         /**
        //          * @brief Compute the dot product of two vectors.
        //          *        \f$ \mathbf{u} \otimes \mathbf{v} = u v^\top \f$
        //          *
        //          * @note Promotes the result to the wider type using @ref PromotedMat2<T, U>.
        //          * @note Operation is restricted to numeric types via @ref StrictArithmetic.
        //          *
        //          * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
        //          *
        //          * @param[in] lhs The first vector to compute the tensor product with.
        //          * @param[in] rhs The second vector to compute the tensor product with.
        //          *
        //          * @return A new 2D matrix containing the tensor product.
        //          */
        //         template <StrictArithmetic U>
        //             requires StrictSignedness<T, U>
        //         [[nodiscard]] static constexpr PromotedMat2<T, U> tensorProduct(const Vec2& lhs, const Vec2& rhs)
        //         noexcept
        //             requires StrictArithmetic<T>;


        /**
         * @brief Compute the 2D pseudo-cross product with another vector.
         *        \f$ \mathbf{a} \times \mathbf{b} = (x_1 \cdot y_2 - x_2 \cdot y_1) \f$
         *
         * @note Operation is restricted to signed numeric types via @ref SignedStrictArithmetic.
         *
         * @param[in] rhs The vector to compute the cross product with.
         *
         * @return The pseudo-cross cross product of the two vectors.
         */
        constexpr T cross(const Vec2& rhs) const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the 2D pseudo-cross product of two vectors.
         *        \f$ \mathbf{a} \times \mathbf{b} = (x_1 \cdot y_2 - x_2 \cdot y_1) \f$
         *
         * @note Operation is restricted to signed numeric types via @ref SignedStrictArithmetic.
         *
         * @param[in] lhs The first vector to compute the cross product with.
         * @param[in] rhs The second vector to compute the cross product with.
         *
         * @return The pseudo-cross product of the two vectors.
         */
        static constexpr T cross(const Vec2& lhs, const Vec2& rhs) noexcept
            requires SignedStrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FALCON_Vec2_Mag
         * @{
         */

        /**
         * @brief Compute the magnitude (Euclidean Norm) of this vector.
         *        \f$ \|\mathbf{v}\| = \sqrt{\mathbf{v} \cdot \mathbf{v}} \f$
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @return The scalar magnitude of the vector.
         */
        [[nodiscard]] constexpr T mag() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the magnitude (Euclidean Norm) of @p Vec.
         *        \f$ \|\mathbf{v}\| = \sqrt{\mathbf{v} \cdot \mathbf{v}} \f$
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[in] vec The vector to compute the magnitude of.
         *
         * @return The scalar magnitude of @p Vec.
         */
        [[nodiscard]] static constexpr T mag(const Vec2& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the magnitude square (Euclidean Norm) of this vector.
         *        \f$ \|\mathbf{v}\| = \mathbf{v} \cdot \mathbf{v} \f$
         *
         * @return The scalar magnitude of the vector.
         */
        [[nodiscard]] constexpr T magSq() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the magnitude square (Euclidean Norm) of @p Vec.
         *        \f$ \|\mathbf{v}\| = \mathbf{v} \cdot \mathbf{v} \f$
         *
         * @param[in] vec The vector to compute the magnitude of.
         *
         * @return The scalar magnitude of @p Vec.
         */
        [[nodiscard]] static constexpr T magSq(const Vec2& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Manhattan length (L1 Norm) of this vector.
         *        \f$ \|\mathbf{v}\|_1 = |x| + |y| \f$
         *
         * @return The Manhattan length.
         */
        [[nodiscard]] constexpr T manhattanNorm() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Manhattan length (L1 Norm) of @p Vec.
         *        \f$ \|\mathbf{v}\|_1 = |x| + |y| \f$
         *
         * @param[in] vec The vector to compute the taxicab norm of.
         *
         * @return The Manhattan length.
         */
        [[nodiscard]] static constexpr T manhattanNorm(const Vec2& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Chebyshev length (L∞ Norm) of this vector.
         *        \f$ \|\mathbf{v}\|_{\infty} = max(|x|, |y|) \f$
         *
         * @return The Chebyshev length.
         */
        [[nodiscard]] constexpr T chebyshevNorm() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Chebyshev length (L∞ Norm) of @p Vec.
         *        \f$ \|\mathbf{v}\|_{\infty} = max(|x|, |y|) \f$
         *
         * @param[in] vec The vector to compute the taxicab norm of.
         *
         * @return The Chebyshev length.
         */
        [[nodiscard]] static constexpr T chebyshevNorm(const Vec2& vec) noexcept
            requires StrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FALCON_Vec2_Dist
         * @{
         */

        /**
         * @brief Compute the Euclidean (L2) distance between this vector and the @p rhs vector.
         *        \f$ d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2} \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @param[in] rhs The target position vector.
         *
         * @return The Euclidean distance promoted as the promoted floating-point type.
         */
        [[nodiscard]] constexpr T dist(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Euclidean (L2) distance between two vectors.
         *        \f$ d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2} \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @param[in] lhs The first position vector.
         * @param[in] rhs The second position vector.
         *
         * @return The Euclidean distance as the promoted floating-point type.
         */
        [[nodiscard]] static constexpr T dist(const Vec2& lhs, const Vec2& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the squared Euclidean (L2) distance between this vector and the @p rhs vector.
         *        \f$ d = (x_2 - x_1)^2 + (y_2 - y_1)^2 \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @param[in] rhs The target position vector.
         *
         * @return The squared Euclidean distance.
         */
        [[nodiscard]] constexpr T distSq(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the squared Euclidean (L2) distance between two vectors.
         *        \f$ d = (x_2 - x_1)^2 + (y_2 - y_1)^2 \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @param[in] lhs The first position vector.
         * @param[in] rhs The second position vector.
         *
         * @return The squared Euclidean distance.
         */
        [[nodiscard]] static constexpr T distSq(const Vec2& lhs, const Vec2& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Manhattan (L1) distance between this vector and the @p rhs vector.
         *        \f$ d = |x_1 - x_2| + |y_1 - y_2| \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The target position vector.
         *
         * @return The Manhattan (Taxicab) distance.
         */
        [[nodiscard]] constexpr T manhattanDist(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Manhattan (L1) distance between two vectors.
         *        \f$ d = |x_1 - x_2| + |y_1 - y_2| \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The first position vector.
         * @param[in] rhs The second position vector.
         *
         * @return The Manhattan(Taxicab) distance.
         */
        [[nodiscard]] static constexpr T manhattanDist(const Vec2& lhs, const Vec2& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Chebyshev (L∞) distance between this vector and the @p rhs vector.
         *        \f$ d = \max{(|x_2 - x_1|, |y_2 - y_1|)} \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The target position vector.
         *
         * @return The Chebyshev distance.
         */
        [[nodiscard]] constexpr T chebyshevDist(const Vec2& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Chebyshev (L∞) distance between two vectors.
         *        \f$ d = \max{(|x_2 - x_1|, |y_2 - y_1|)} \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The first position vector.
         * @param[in] rhs The second position vector.
         *
         * @return The Chebyshev distance.
         */
        [[nodiscard]] static constexpr T chebyshevDist(const Vec2& lhs, const Vec2& rhs) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_Vec2_Normalize
         * @{
         */

        /**
         * @brief Compute the normalized (unit) form of this vector.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note Performs assertion for division by zero, resulting from zero-length vector,
         *       in **Debug mode**.
         * @note Restricted to floating point types via @ref FPArithmetic.
         *
         * @return A new @ref Vec2 with a magnitude of 1.0.
         */
        [[nodiscard]] constexpr Vec2<Magnitude<T>> normalize() const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Compute the normalized (unit) form of @p Vec.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note Performs assertion for division by zero, resulting from zero-length vector,
         *       in **Debug mode**.
         * @note Restricted to floating point types via @ref FPArithmetic.
         *
         * @param[in] vec The vector to normalize.
         *
         * @return A new @ref Vec2 with a magnitude of 1.0.
         */
        [[nodiscard]] static constexpr Vec2<Magnitude<T>> normalize(const Vec2& vec) noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Compute the normalized (unit) form of this vector.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note This is a safe operation. If the vector's magnitude falls below the internal
         *       epsilon, or if it contains NaN components, division by zero is bypassed.
         * @note Restricted to floating point types via @ref FPArithmetic.
         *
         * @return A @ref Vec2 with a magnitude of 1.0, or a zero-vector if the original magnitude is below
         *         the epsilon threshold or if this vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vec2<Magnitude<T>> safeNormalize() const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Compute the normalized (unit) form of @p Vec.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note This is a safe operation. If the vector's magnitude falls below the internal
         *       epsilon, or if it contains NaN components, division by zero is bypassed.
         * @note Restricted to floating point types via @ref FPArithmetic.
         *
         * @param[in] vec The vector to be normalized.
         *
         * @return A @ref flcn::Vec2 with a magnitude of 1.0, or a zero-vector if the original magnitude is
         *         below the epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr Vec2<Magnitude<T>> safeNormalize(const Vec2& vec) noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Compute the normalized (unit) form of this vector and
         *        set @p status to the normalization operation result.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note This is a safe operation. If the vector's magnitude falls below the internal
         *       epsilon, or if it contains NaN components, division by zero is bypassed.
         * @note Restricted to floating point types via @ref FPArithmetic.
         *
         * @param[out] status The status flag to store the status of the current operation result.*
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return A @ref flcn::Vec2 with a magnitude of 1.0, or a zero-vector if the original magnitude is
         *         below the epsilon threshold or if this vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vec2<Magnitude<T>> tryNormalize(OperationStatus& status) const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Compute the normalized (unit) form of @p Vec and
         *        set @p status to the normalization operation result.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note This is a safe operation. If the vector's magnitude falls below the internal
         *       epsilon, or if it contains NaN components, division by zero is bypassed.
         * @note Restricted to floating point types via @ref FPArithmetic.
         *
         * @param[in] vec     The vector to be normalized.
         * @param[out] status The status flag to store the status of the current operation result.*
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return A @ref flcn::Vec2 with a magnitude of 1.0, or a zero-vector if the original magnitude is
         *         below the epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr Vec2<Magnitude<T>> tryNormalize(const Vec2& vec,
                                                                       OperationStatus& status) noexcept
            requires FPArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FALCON_Vec2_Proj
         * @{
         */

        /// API NOTE: While projections are allowed on all numeric types, it can cause imprecise results with
        ///           non-floating point types due to rounding in the division, so they are restricted to only
        ///           floating point types.

        /**
         * @brief Project this vector onto the @p onto vector.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note If @p onto is normalized, use @ref projectNorm as it is a faster implementation for unit vectors.
         * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
         *
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vec2.
         */
        [[nodiscard]] constexpr Vec2 project(const Vec2& onto) const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Project this vector onto the **unit** @p onto vector.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note Only use this method if @p onto is normalized. If not, use @ref project.
         *
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vec2.
         */
        [[nodiscard]] constexpr Vec2 projectNorm(const Vec2& onto) const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Project the @p Vec vector onto the @p onto vector.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note If @p onto is normalized, use @ref projectNorm as it is a faster implementation for unit vectors.
         * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
         *
         * @param[in] vec  The vector to project.
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vec2.
         */
        [[nodiscard]] static constexpr Vec2 project(const Vec2& vec, const Vec2& onto) noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Project the @p Vec vector onto the **unit** @p onto vector.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note Only use this method if @p onto is normalized. If not, use @ref project.
         *
         * @param[in] vec  The vector to project.
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vec2.
         */
        [[nodiscard]] static constexpr Vec2 projectNorm(const Vec2& vec, const Vec2& onto) noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Project this vector onto the @p onto vector.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, projection is bypassed.
         * @note If @p onto is normalized, use @ref safeProjectNorm as it is a faster implementation for unit vectors.
         *
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vec2 or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vec2 safeProject(const Vec2& onto) const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Project this vector onto the **unit** @p onto vector.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
         * @note Only use this method if @p onto is normalized. If not, use @ref safeProject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto           The vector to project onto.
         *
         * @return The projected @ref Vec2 or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vec2 safeProjectNorm(const Vec2& onto) const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Project the @p Vec vector onto the @p onto vector.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, projection is bypassed.
         * @note If @p onto is normalized, use @ref safeProjectNorm as it is a faster implementation for unit vectors.
         *
         *
         * @param[in] vec  The vector to project.
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vec2 or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr Vec2 safeProject(const Vec2& vec, const Vec2& onto) noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Project the @p Vec vector onto the **unit** @p onto vector.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
         * @note Only use this method if @p onto is normalized. If not, use @ref safeProject.
         *
         * @param[in] vec  The vector to project.
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vec2 or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr Vec2 safeProjectNorm(const Vec2& vec, const Vec2& onto) noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Project this vector onto the @p onto vector and set @p status to the
         *        projection operation result.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, projection is bypassed.
         * @note If @p onto is normalized, use @ref tryProjectNorm as it is a faster implementation for unit vectors.
         *
         * @param[in] onto    The vector to project onto.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The projected @ref Vec2 or a zero-vector if projected onto a zero-length vector or if
         *         either vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vec2 tryProject(const Vec2& onto, OperationStatus& status) const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Project this vector onto the **unit** @p onto vector and set @p status to the
         *        projection operation result.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
         * @note Only use this method if @p onto is normalized. If not, use @ref tryProject.
         *
         *
         * @param[in] onto    The vector to project onto.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The projected @ref Vec2 or a zero-vector if projected onto a zero-length vector or if
         *         either vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vec2 tryProjectNorm(const Vec2& onto, OperationStatus& status) const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Project the @p Vec vector onto the @p onto vector and set @p status to the
         *        projection operation result.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, projection is bypassed.
         * @note If @p onto is normalized, use @ref tryProjectNorm as it is a faster implementation for unit vectors.
         *
         *
         * @param[in] vec     The vector to project.
         * @param[in] onto    The vector to project onto.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The projected @ref Vec2 or a zero-vector if projected onto a zero-length vector or if
         *         either vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr Vec2 tryProject(const Vec2& vec, const Vec2& onto,
                                                       OperationStatus& status) noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Project the @p Vec vector onto the **unit** @p onto vector and set @p status to the
         *        projection operation result.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
         * @note Only use this method if @p onto is normalized. If not, use @ref tryProject.
         *
         * @param[in] vec     The vector to project.
         * @param[in] onto    The vector to project onto.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The projected @ref Vec2 or a zero-vector if projected onto a zero-length vector or if
         either
         *         vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr Vec2 tryProjectNorm(const Vec2& vec, const Vec2& onto,
                                                           OperationStatus& status) noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Reject this vector from the @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note If @p from is normalized, use @ref rejectNorm as it is a faster implementation for unit vectors.
         * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
         *
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vec2 component.
         */
        [[nodiscard]] constexpr Vec2 reject(const Vec2& from) const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Reject this vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note Only use this method if @p from is normalized. If not, use @ref reject.
         *
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vec2 component.
         */
        [[nodiscard]] constexpr Vec2 rejectNorm(const Vec2& from) const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Reject the @p Vec vector from the @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note If @p from is normalized, use @ref rejectNorm as it is a faster implementation for unit vectors.
         *
         * @param[in] vec  The vector to be rejected.
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vec2 component.
         */
        [[nodiscard]] static constexpr Vec2 reject(const Vec2& vec, const Vec2& from) noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Reject the @p Vec vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note Only use this method if @p from is normalized. If not, use @ref reject.
         *
         * @param[in] vec The vector to be rejected.
         * @param[in] from   The vector to reject from.
         *
         * @return The perpendicular @ref Vec2 component.
         */
        [[nodiscard]] static constexpr Vec2 rejectNorm(const Vec2& vec, const Vec2& from) noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Reject this vector from the @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, rejection is bypassed.
         * @note If @p from is normalized, use @ref safeRejectNorm as it is a faster implementation for unit vectors.
         *
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vec2 safeReject(const Vec2& from) const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Reject this vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
         * @note Only use this method if @p from is normalized. If not, use @ref safeReject.
         *
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vec2 safeRejectNorm(const Vec2& from) const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Reject the @p Vec vector from the @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, rejection is bypassed.
         * @note If @p from is normalized, use @ref safeRejectNorm as it is a faster implementation for unit vectors.
         *
         * @param[in] vec  The vector to reject.
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr Vec2 safeReject(const Vec2& vec, const Vec2& from) noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Reject the @p Vec vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
         * @note Only use this method if @p from is normalized. If not, use @ref safeReject.
         *
         * @param[in] vec  The vector to reject.
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr Vec2 safeRejectNorm(const Vec2& vec, const Vec2& from) noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Reject this vector from the @p from vector and set @p status to the result of rejection operation.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, rejection is bypassed.
         * @note If @p from is normalized, use @ref tryRejectNorm as it is a faster implementation for unit vectors.
         *
         * @param[in] from    The vector to reject from
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The perpendicular @ref Vec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vec2 tryReject(const Vec2& from, OperationStatus& status) const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Reject this vector from the **unit** @p from vector and set @p status to the result of
         *        rejection operation.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
         * @note Only use this method if @p from is normalized. If not, use @ref tryReject.
         *
         * @param[in] from    The vector to reject from
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The perpendicular @ref Vec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vec2 tryRejectNorm(const Vec2& from, OperationStatus& status) const noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Reject the @p Vec vector from the @p from vector and set @p status to the result of
         *        rejection operation.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, rejection is bypassed.
         * @note If @p from is normalized, use @ref tryRejectNorm as it is a faster implementation for unit vectors.
         *
         *
         * @param[in] vec     The vector to reject.
         * @param[in] from    The vector to reject from.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The perpendicular @ref Vec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr Vec2 tryReject(const Vec2& vec, const Vec2& from,
                                                      OperationStatus& status) noexcept
            requires FPArithmetic<T>;


        /**
         * @brief Reject the @p Vec vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
         * @note Only use this method if @p from is normalized. If not, use @ref tryReject.
         *
         * @param[in] vec     The vector to reject.
         * @param[in] from    The vector to reject from.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The perpendicular @ref Vec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr Vec2 tryRejectNorm(const Vec2& vec, const Vec2& from,
                                                          OperationStatus& status) noexcept
            requires FPArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FALCON_Vec2_Utils
         * @{
         */

        /**
         * @brief Check if any component of this vector is an IEEE 754 infinity.
         *
         * @note Always return false for integral types.
         *
         * @return True if at least one component is positive or negative infinity.
         */
        [[nodiscard]] constexpr bool hasInf() const noexcept;


        /**
         * @brief Check if any component of a vector is an IEEE 754 infinity.
         *
         * @note Always return false for integral types.
         *
         * @param[in] vec The vector to evaluate for indefinite components.
         *
         * @return True if at least one component is positive or negative infinity.
         */
        [[nodiscard]] static constexpr bool hasInf(const Vec2& vec) noexcept;


        /**
         * @brief Check if any component of this vector is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @return True if at least one component is NaN.
         */
        [[nodiscard]] constexpr bool hasNaN() const noexcept;


        /**
         * @brief Check if any component of this vector is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @param[in] vec The vector to evaluate for indefinite components.
         *
         * @return True if at least one component is NaN.
         */
        [[nodiscard]] static constexpr bool hasNaN(const Vec2& vec) noexcept;

        /** @} */


        /**
         * @addtogroup FALCON_Vec2_Log
         * @{
         */

        /**
         * @brief Write the vector to an output stream.
         *        Format the vector as <x, y> string representation for debugging or logging.
         *
         * @param os     The output stream to write to.
         * @param vector The vector to be streamed.
         *
         * @return A reference to the output stream @p os.
         */
        friend std::ostream& operator<<(std::ostream& os, const Vec2& vector)
        {
            const std::streamsize oldPrecision     = os.precision();
            const std::ios_base::fmtflags oldFlags = os.flags();

            auto precision = Config::useFullPrecision
                ? std::is_same_v<T, double> ? Config::DOUBLE_PRECISION : Config::FLOAT_PRECISION
                : Config::LOG_PRECISION;
            os << std::setprecision(precision) << std::fixed;

            // Stack spill the values from the register so we can stream it to os.
            alignas(16) T data[DIMENSION];
            vector._data.storeAligned(data);

            os << "<" << data[0] << ", " << data[1] << ">\n";

            os.precision(oldPrecision);
            os.flags(oldFlags);

            return os;
        }

        /** @} */

        /**
         * @addtogroup FALCON_Vec2_Const
         * @{
         */

        /*************************************
         *                                   *
         *            CONSTANTS              *
         *                                   *
         *************************************/

        // NOLINTBEGIN

        /**
         * @brief A 2D vector with all components set to one (1, 1).
         */
        static constexpr Vec2 one()
            requires StrictArithmetic<T>
        { return Vec2{ T(1), T(1) }; }


        /**
         * @brief A 2D vector with all components set to zero (0, 0).
         */
        static constexpr Vec2 zero()
            requires StrictArithmetic<T>
        { return Vec2{ T(0), T(0) }; }


        /**
         * @brief A 2D vector with all components set to positive infinity.
         *
         * @note Constrained to floating point types.
         */
        static constexpr Vec2 inf()
            requires std::floating_point<T>
        { return Vec2{ T(constants::INFINITY_D), T(constants::INFINITY_D) }; }


        /**
         * @brief A 2D vector with all components set to negative infinity.
         *
         * @note Constrained to floating point types.
         */
        static constexpr Vec2 infNeg()
            requires std::floating_point<T>
        { return Vec2{ T(-constants::INFINITY_D), T(-constants::INFINITY_D) }; }


        /**
         * @brief A 2D vector with all components set to Not-A-Number (NaN).
         *
         * @note Constrained to floating point types.
         */
        static constexpr Vec2 qnan()
            requires std::floating_point<T>
        { return Vec2{ T(constants::NaN_D), T(constants::NaN_D) }; }


        /**
         * @brief A 2D unit vector aligned with the positive X-axis (1, 0).
         *
         * @note Constrained to signed types.
         */
        static constexpr Vec2 right()
            requires std::is_signed_v<T>
        { return Vec2{ T(1), T(0) }; }


        /**
         * @brief A 2D unit vector aligned with the negative X-axis (-1, 0).
         *
         * @note Constrained to signed types.
         */
        static constexpr Vec2 left()
            requires std::is_signed_v<T>
        { return Vec2{ T(-1), T(0) }; }


        /**
         * @brief A 2D unit vector aligned with the positive Y-axis (0, 1).
         *
         * @note Constrained to signed types.
         */
        static constexpr Vec2 up()
            requires std::is_signed_v<T>
        { return Vec2{ T(0), T(1) }; }


        /**
         * @brief A 2D unit vector aligned with the negative Y-axis (0, -1).
         *
         * @note Constrained to signed types.
         */
        static constexpr Vec2 down()
            requires std::is_signed_v<T>
        { return Vec2{ T(0), T(-1) }; }

        // NOLINTEND

        /** @} */

    private:
        flcn::Simd128_t<T, DIMENSION> _data;


        /**************************************
         *          MUTATION PROXY            *
         **************************************/

        /// Proxy that enables indexing for Vec2 indexing since Simd128 doesn't support indexed write.
        class IndexableProxy
        {
        public:
            FALCON_INLINE constexpr IndexableProxy(Vec2& parent, const size_t index) noexcept
                : _vec{ parent }, _index{ index }
            {}

            FALCON_INLINE constexpr IndexableProxy& operator=(T value) noexcept
            {
                _vec._data.setAt(_index, value);
                return *this;
            }

            // Allows for operator chaining
            FALCON_INLINE constexpr IndexableProxy& operator=(const IndexableProxy& other) noexcept
            {
                _vec._data.setAt(_index, static_cast<T>(other));
                return *this;
            }

            // Implicit conversion
            FALCON_INLINE constexpr operator T() const noexcept { return _vec._data.getAt(_index); }


        private:
            Vec2& _vec;
            size_t _index;
        };


        /// Proxy that enables indexing with compile-time known indices.
        /// @tparam Index The index to use for indexing.
        template <size_t Index>
        class ConstIndexableProxy
        {
        public:
            FALCON_INLINE constexpr ConstIndexableProxy(Vec2& parent) noexcept: _vec{ parent } {}

            FALCON_INLINE constexpr ConstIndexableProxy& operator=(T value) noexcept
            {
                _vec._data.template setAt<Index>(value);
                return *this;
            }

            // Allows for operator chaining(a = b = c)
            FALCON_INLINE constexpr ConstIndexableProxy& operator=(const ConstIndexableProxy& other) noexcept
            {
                _vec._data.template setAt<Index>(static_cast<T>(other));
                return *this;
            }

            // Implicit conversion
            FALCON_INLINE constexpr operator T() const noexcept { return _vec._data.template getAt<Index>(); }

        private:
            Vec2& _vec;
        };
    };



    /*************************************
     *       NON-MEMBER FUNCTIONS        *
     *************************************/

    /**
     * @addtogroup FALCON_Vec2_Arithmetic
     * @{
     */

    /**
     * @brief Scale the vector by a scalar value.
     *        Multiply @p scalar by each component of the vector and returns a new vector.
     *
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @warning The scalar will be cast to the numeric type of the vector.
     *
     * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] scalar The value to scale by.
     * @param[in] vector The vector to scale[RHS].
     *
     * @return A new @ref Vec2 scaled by @p scalar.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    [[nodiscard]] constexpr Vec2<T> operator*(S scalar, const Vec2<T>& vector) noexcept
        requires StrictArithmetic<T>;

    /** @} */


    /**
     * @addtogroup FALCON_Vec2_Alias
     * @{
     */

    /*************************************
     *             ALIASES               *
     *************************************/

    using Vec2B   = Vec2<int8_t>;   ///< Signed Byte (8-bit) vector
    using Vec2UB  = Vec2<uint8_t>;  ///< Unsigned Byte (8-bit) vector
    using Vec2I   = Vec2<int32_t>;  ///< Signed Int (32-bit) vector
    using Vec2U   = Vec2<uint32_t>; ///< Unsigned Int (32-bit) vector
    using Vec2F   = Vec2<float>;    ///< Single Precision Floating Point (32-bit) vector
    using Vec2LL  = Vec2<int64_t>;  ///< Signed Long Long (64-bit) vector
    using Vec2D   = Vec2<double>;   ///< Double Precision Floating Point (64-bit) vector
    using Vec2ULL = Vec2<uint64_t>; ///< Unsigned Long Long (64-bit) vector

    /** @} */


    /** @brief Template deduction guide for Vec2 */
    template <typename T>
        requires Arithmetic<T>
    Vec2(T, T) -> Vec2<T>;

} // namespace flcn


#include "Vec2.tpp"
