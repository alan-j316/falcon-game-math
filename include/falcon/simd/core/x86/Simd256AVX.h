#pragma once
/**
 * @file Simd256AVX.h
 * @author Alan Abraham P Kochumon
 * @date Created on: October 10, 2026
 *
 * @brief AVX+ implementation for Simd256.
 *
 * @details 256-bit SIMD register wrapper for x64-based systems.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "falcon/core/Preprocessors.h"
#include "falcon/simd/core/RegisterTraits.h"
#include "falcon/simd/utils/SimdTraits.h"

#include <bit>
#include <emmintrin.h>
#include <immintrin.h>

namespace flcn
{

    /**
     * @brief 256-bit Simd Register specialized for AVX architecture.
     *
     * @tparam DataType The word-width/data type of the register.
     * @tparam Lane     The number of data lanes. Must be a power of 2 and the total width in bits(size * Lane) must
     be
     *                  less than 256.
     */
    template <typename DataType, size_t Lane>
    struct alignas(32) Simd256<SimdBackend::ARCH_AVX, DataType, Lane>
    {

        static constexpr size_t BufferWidth  = 256;      ///< Width of the register in bits.
        using ValueType                      = DataType; ///< The internal data type of this Register.
        static constexpr size_t LaneCount    = Lane;     ///< Number of Lanes of current SIMD256 Register
        static constexpr size_t MaxLaneCount = BufferWidth / (sizeof(DataType) * 8); /// Maximum Lanes in this
        static constexpr size_t Alignment    = 32;                                   ///< Required alignment.

        static_assert(sizeof(DataType) * Lane * 8 <= BufferWidth && "Invalid size.");
        static_assert(std::has_single_bit(Lane) && Lane > 1 &&
                      "Invalid Number of Lanes. Must be a power of 2(2, 4, 8, 16...)");


        constexpr explicit Simd256() = default;

        /**
         * @brief Initialize a 256-bit SIMD register with @p data.
         *
         * @tparam Args The numeric type of @p data. Must match the register's datatype.
         * @param data  The values to initialize the register with.
         *
         * @note If only a single argument is provided then the value will be broadcasted across the entire
         register.
         *       The number of values provided must be less than or equal to the total register lanes. If
         *       the number of values is less than the lanes, values will be inserted into the lower lanes,
         *       and rest filled with zeroes.
         */
        template <typename... Args>
            requires(SimdSafeConvertible<Args, DataType> && ...)
        constexpr explicit Simd256(Args&&... data) noexcept;


        // // TODO: Add test
        // /// @brief Cast a register from @p DataType to @p T.
        // /// @tparam T The destination data type.
        // template <typename T>
        // [[nodiscard]] constexpr Simd256<SimdBackend::ARCH_AVX, T, Lane> cast() const noexcept;


        //     /// @brief Cast a register from @p DataType to @p T (non-const variant).
        //     /// @tparam T The destination data type.
        //     template <typename T>
        //     [[nodiscard]] constexpr Simd256<SimdBackend::ARCH_AVX, T, Lane> cast() noexcept;


        /**
         * @brief Initialize a 256-bit SIMD register with values from a std::container(std::array, std::vector).
         *
         * @note Unused lanes must be zeroed-out manually.
         *
         * @param values The values to fill the register with.
         *
         * @warning The container must be aligned to 32-byte boundary. For unaligned data,
         *          use @ref load to load data manually.
         */
        constexpr explicit Simd256(std::span<const DataType> values) noexcept;

        /**
         * @brief Initialize a 256-bit SIMD register with a raw memory buffer.
         *
         * @note Passing in a buffer with allocated size less than @p Lane * @p sizeof(DataType)
         *       can cause segmentation faults.
         * @note Unused lanes must be zeroed-out manually.
         *
         * @param pBuffer The starting address of the values to fill the register with.
         *
         * @warning @p buffer must be aligned to 32-byte boundary. For unaligned data,
         *          use @ref load to load data manually.
         */
        constexpr explicit Simd256(const DataType* pBuffer) noexcept;


        // TODO: Add Test
        /// @brief Initialize a Simd256 register with a primitive register type.
        explicit constexpr Simd256(simd::internal::Simd256Register_t<CURRENT_SIMD_BACKEND, DataType, Lane> reg)
            : _reg(reg)
        {}


        /**
         * @brief Set the register with the given values in the lower lanes filling the unfilled lanes with zeroes.
         *
         * @note Internally the register gets filled from the bottom to top, but when used with store
         *       to retrieve the value, the values will be identical.
         *       set(1, 2) => [0, 0, 2, 1] => store() => [1, 2]
         * @note Unused lanes are zeroed out.
         *
         * @tparam Args The numeric type of arguments. Must be less than the maximum lane size.
         *
         * @param args The data to put in the register.
         *
         * @return A reference to this register.
         */
        template <typename... Args>
            requires(sizeof...(Args) <= Lane) && (std::same_as<Args, DataType> && ...) &&
            (SimdSafeConvertible<Args, DataType> && ...)
        constexpr Simd256& set(Args... args);


        /**
         * @brief Load data from memory into the SIMD register.
         *
         * @note Data must be aligned to 32-byte boundary.
         *       If the size * Lane cannot saturate the buffer, data will be moved to lower lanes.
         *       Example: loadAligned<2>(uint8_t*) will only load the lower 16 bits with the data and
         *       fill the rest with zeroes.
         *
         * @param data The data to load.
         */
        constexpr void loadAligned(const DataType* data) noexcept;


        /**
         * @brief Load data from memory into the SIMD register.
         *
         * @note Can work with unaligned memory.
         *       If the size * Lane cannot saturate the buffer, data will be moved to lower lanes.
         *       Example: loadAligned<2>(uint8_t*) will only load the lower 16 bits with the data and fill the
         *       rest with zeroes.
         *
         * @param data The data to load.
         *
         * @relatedalso loadAligned(DataType*)
         * @relatedalso store(DataType*)
         * @relatedalso storeAligned(DataType*)
         * @relatedalso broadcast(DataType)
         * @relatedalso setZero()
         */
        constexpr void load(const DataType* data) noexcept;


        /**
         * @brief Broadcast single value across the whole simd register.
         *
         * @details
         *        Fills the entire register lane with the same value, i.e, for 32-bit floats, all the 4 lanes
         will
         *        contain the same @p value.
         * @param value The value to broadcast.
         *
         * @relatedalso load(DataType*)
         * @relatedalso loadAligned(DataType*)
         * @relatedalso store(DataType*)
         * @relatedalso storeAligned(DataType*)
         * @relatedalso setZero()
         */
        constexpr void broadcast(DataType value) noexcept;


        /**
         * @brief Zero out the register.
         *
         * @relatedalso load(DataType*)
         * @relatedalso loadAligned(DataType*)
         * @relatedalso store(DataType*)
         * @relatedalso storeAligned(DataType*)
         * @relatedalso broadcast(DataType)
         * @relatedalso setOne()
         */
        constexpr void setZero() noexcept;


        /**
         * @brief Set all the bits in the register to 1.
         *
         * @relatedalso load(DataType*)
         * @relatedalso loadAligned(DataType*)
         * @relatedalso store(DataType*)
         * @relatedalso storeAligned(DataType*)
         * @relatedalso broadcast(DataType)
         * @relatedalso setZero()
         */
        constexpr void setOne() noexcept;


        /**
         * @brief Store the current register value buffer.
         *
         * @note The provided buffer must have enough size to hold the data.
         * @note The buffer only fills upto the lane size of the register. This means that if you pass-in
         *       an array of big enough to hold 4 int64_t but the Lane is 2, then it will only fill the
         *       upper two elements, i.e [0, 1, _, _]
         *
         * @param pBuffer The buffer to write the data to.
         *
         * @relatedalso load(DataType*)
         * @relatedalso loadAligned(DataType*)
         * @relatedalso storeAligned(DataType*)
         * @relatedalso broadcast(DataType)
         * @relatedalso setZero()
         */
        constexpr void store(DataType* pBuffer) const noexcept;


        /**
         * @brief Store the current register values into a 32-byte aligned buffer.
         *
         * @note The provided buffer must have enough size to hold the data.
         *
         * @param pBuffer The buffer to write the data to.
         *
         * @relatedalso load(DataType*)
         * @relatedalso loadAligned(DataType*)
         * @relatedalso store(DataType*)
         * @relatedalso broadcast(DataType)
         * @relatedalso setZero()
         */
        constexpr void storeAligned(DataType* pBuffer) const noexcept;


        /**
         * Get the value at @p index.
         *
         * @param index The index of the register. Must be between 0 and Lane - 1.
         *
         * @note For indices known at compile-time, use get<Index>() as it is faster
         *       due to the availability of direct hardware intrinsic.
         *
         * @return The value at index [read-only].
         *
         * @relatedalso setAt(size_t, DataType)
         * @relatedalso getAt<size_t>()
         * @relatedalso setAt<size_t>(DataType)
         */
        [[nodiscard]] constexpr DataType getAt(size_t index) const noexcept;


        //     /**
        //      * @brief Set the value at @p index to @p value.
        //      *
        //      * @param index The index of the register. Must be between 0 and Lane - 1.
        //      * @param value The value to set.
        //      *
        //      * @note For indices known at compile-time, use set<Index>(value) as it is faster
        //      *       due to the availability of direct hardware intrinsic.
        //      *
        //      * @relatedalso getAt(size_t)
        //      * @relatedalso getAt<size_t>()
        //      * @relatedalso setAt<size_t>(DataType)
        //      */
        //     constexpr void setAt(size_t index, DataType value) noexcept;


        /**
         * @brief Get the value at @p index.
         *
         * @tparam Index The index of the register. Must be between 0 and Lane - 1.
         *
         * @return The value at index [read-only].
         *
         * @relatedalso getAt(size_t)
         * @relatedalso setAt(size_t, DataType)
         * @relatedalso setAt<size_t>(DataType)
         */
        template <size_t Index>
            requires(Index < Lane)
        [[nodiscard]] constexpr DataType getAt() const noexcept;


        /**
         * @brief Set the value at @p index to @p value.
         *
         * @tparam Index The index of the register. Must be between 0 and Lane - 1.
         *
         * @return The value at index [read-only].
         *
         * @relatedalso getAt(size_t)
         * @relatedalso setAt(size_t, DataType)
         * @relatedalso getAt<size_t>()
         */
        template <size_t Index>
            requires(Index < Lane)
        constexpr void setAt(DataType value) noexcept;


        /// @brief Get the element from the lowest lane(0-th index).
        constexpr DataType extractFirst() noexcept;


        ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        ///    BITWISE OPERATIONS
        ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        // TODO: Add bitwise |=, &= ^= etc.
        /// @brief Perform bitwise NOT on the entire register.
        [[nodiscard]] constexpr Simd256 operator~() const noexcept;

        /// @brief Perform bitwise AND between this register and @p other.
        [[nodiscard]] constexpr Simd256 operator&(Simd256 other) const noexcept;

        /// @brief Perform bitwise OR between this register and @p other.
        [[nodiscard]] constexpr Simd256 operator|(Simd256 other) const noexcept;

        /// @brief Perform bitwise OR between this register and @p other.
        [[nodiscard]] constexpr Simd256 operator^(Simd256 other) const noexcept;

        /// @brief Perform a bitwise `and_not` combination between this register and @p other.
        /// @note  Faster than manually doing (~RegA & RegB) since this executes only a single SIMD instruction.
        [[nodiscard]] constexpr Simd256 andNot(Simd256 other) const noexcept;
        //
        //     /// @brief Perform an OR operation on the entire vector, horizontally.
        //     [[nodiscard]] constexpr DataType horizontalOr() const noexcept;
        //
        //     /// @brief Perform an AND operation on the entire vector, horizontally.
        //     [[nodiscard]] constexpr DataType horizontalAnd() const noexcept;



        ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        ///   ARITHMETIC OPERATIONS
        ///+=+=+=+=+=+=+=+=+=+=+=+=+=

        /**
         * @brief Add two registers together and return a new register.
         *
         * @note Register arithmetic to limited is same data types and lanes.
         *
         * @param other The register to add.
         *
         * @return A new register with the sum elements from this register and @p other.
         */
        [[nodiscard]] constexpr Simd256 operator+(Simd256 other) const noexcept;


        /**
         * @brief Add contents of this register with @p other in-place.
         *
         * @note Register arithmetic to limited is same data types and lanes.
         *
         * @param other The register to add.
         *
         * @return A reference to this register with sum.
         */
        constexpr Simd256& operator+=(Simd256 other) noexcept;


        /**
         * @brief Subtract two registers and return a new register.
         *
         * @note Register arithmetic is limited to same data types and lanes.
         *
         * @param other The register to subtract.
         * @return A new register with the difference between elements of this register and @p other.
         */
        [[nodiscard]] constexpr Simd256 operator-(Simd256 other) const noexcept;


        /**
         * @brief Subtract contents of this register from @p other in-place.
         *
         * @note Register arithmetic is limited to same data types and lanes.
         *
         * @param other The register to subtract.
         *
         * @return A reference to this register with difference.
         */
        constexpr Simd256& operator-=(Simd256 other) noexcept;


        /**
         * @brief Perform a arithmetic negation on this register(NOT BITWISE) and return a new register.
         *        Analogous to (0 - reg) or -reg.
         * @return A new register with negated elements.
         */
        [[nodiscard]] constexpr Simd256 operator-() const noexcept;


        /**
         * @brief Multiply two registers and return a new register.
         *
         * @note Register arithmetic is limited to same data types and lanes.
         *
         * @param other The register to multiply.
         * @return A new register with the product of elements of this register and @p other.
         */
        [[nodiscard]] constexpr Simd256 operator*(Simd256 other) const noexcept;


        /**
         * @brief Multiply contents of this register with @p other in-place.
         *
         * @note Register arithmetic is limited to same data types and lanes.
         *
         * @param other The register to multiply.
         *
         * @return A reference to this register with products.
         */
        constexpr Simd256& operator*=(Simd256 other) noexcept;


        /**
         * @brief Divide contents of this register by another register(@p other).
         *
         * @note Register arithmetic is limited to same data types and lanes.
         * @note Direct SIMD operations are limited to floating-point numbers only.
         *       Therefore the operations for integrals are emulated by converting them to floating points, but some
         *       integrals like for `uint64_t` and `int64_t` are fully scalar since converting them to floating point
         *       can lead to precision loss due to the 53-bit maximum precision of double precision float point numbers.
         *
         * @note For division with same divisor it is faster to use operator/ or operator/= which implements division
         *       by constant from Hackers Delight. (TODO)
         *
         * @param other The register containing the divisors.
         *
         * @return A new register with the quotient.
         *
         * @relatedalso operator/(const DataType)
         * @relatedalso operator/=(const DataType)
         */
        [[nodiscard]] constexpr Simd256 divReg(Simd256 other) const noexcept;


        /**
         * @brief Divide contents of this register by a @p scalar.
         * @todo Update to use division by constant and update readme
         *
         * @note Register arithmetic is limited to same data types and lanes.
         * @note For integral division with different divisors @ref divReg may be
         *       faster.
         *
         * @param scalar The divisor.
         *
         * @return A new register with the quotient.
         *
         * @relatedalso divReg(const Simd256)
         * @relatedalso operator/=(const DataType)
         */
        [[nodiscard]] constexpr Simd256 operator/(DataType scalar) const noexcept;


        /**
         * @brief Divide contents of this register by a @p scalar in-place.
         * @todo Update to use division by constant and update readme
         *
         * @note Register arithmetic is limited to same data types and lanes.
         * @note For integral division with different divisors @ref divReg may be
         *       faster.
         *
         * @param scalar The divisor.
         *
         * @return A reference to this register with products.
         *
         * @relatedalso divReg(const Simd256)
         * @relatedalso operator/(const DataType)
         */
        constexpr Simd256& operator/=(DataType scalar) noexcept;


        /**
         * @brief Perform a fused multiply and add (this * b + c).
         *
         * @note Register arithmetic is limited to same data types and lanes.
         * @param b The register to multiply with this register.
         * @param c The register to add to the product.
         *
         * @return A new register with the fma result.
         */
        [[nodiscard]] constexpr Simd256 fma(Simd256 b, Simd256 c) const noexcept;


        //     /**
        //      * @brief Add together elements from all the lanes of the current register.
        //      * @return The sum of elements in all the lanes.
        //      */
        //     [[nodiscard]] constexpr DataType horizontalAdd() const noexcept;
        //
        //
        //     /**
        //      * @brief Subtract upper lane elements from the lower lanes of the current register.
        //      * @return The difference between elements in all the lanes.
        //      */
        //     [[nodiscard]] constexpr DataType horizontalSub() const noexcept;
        //
        //
        //     //     // TODO: Add masked variants comparison AVX512(__mmask) and emulate


        ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        ///   COMPARISON/EQUALITY
        ///+=+=+=+=+=+=+=+=+=+=+=+=+=

        [[nodiscard]] constexpr Simd256 operator==(Simd256 other) const noexcept;

        [[nodiscard]] constexpr Simd256 operator!=(Simd256 other) const noexcept;

        [[nodiscard]] constexpr Simd256 operator>(Simd256 other) const noexcept;

        [[nodiscard]] constexpr Simd256 operator>=(Simd256 other) const noexcept;

        [[nodiscard]] constexpr Simd256 operator<(Simd256 other) const noexcept;

        [[nodiscard]] constexpr Simd256 operator<=(Simd256 other) const noexcept;

        /**
         * @brief Perform a logical left shift on this register by @p count.
         *
         * @warning If @p count is known at compile time then it is recommended to use
         *          @ref shiftLeft<uint32_t> as it is faster.
         *
         * @return A new 256-bit register with shifted values.
         *
         * @relatedalso operator<<=(uint32_t)
         * @relatedalso operator>>(uint32_t)
         * @relatedalso operator>>=(uint32_t)
         * @relatedalso shiftRightLogical(uint32_t)
         * @relatedalso shiftLeft<uint32_t>()
         * @relatedalso shiftRightArithmetic<uint32_t>()
         * @relatedalso shiftRightLogical<uint32_t>()
         */
        [[nodiscard]] constexpr Simd256 operator<<(uint32_t count) const noexcept;


        /**
         * @brief Perform a logical left shift on this register by @p count in-place.
         *
         * @warning If @p count is known at compile time then it is recommended to use
         *          @ref shiftLeft<uint32_t> as it is faster.
         *
         * @return A reference to this register.
         *
         * @relatedalso operator<<(uint32_t)
         * @relatedalso operator>>(uint32_t)
         * @relatedalso operator>>=(uint32_t)
         * @relatedalso shiftRightLogical(uint32_t)
         * @relatedalso shiftLeft<uint32_t>()
         * @relatedalso shiftRightArithmetic<uint32_t>()
         * @relatedalso shiftRightLogical<uint32_t>()
         */
        constexpr Simd256& operator<<=(uint32_t count) noexcept;


        /**
         * @brief Perform a arithmetic/logical(type dependent) right shift by @p count and return a new register.
         *
         * @warning If @p count is known at compile time then it is recommended to use @ref shiftRight<Count> as
         *          it is faster.
         *
         * @return A new 256-bit register with shifted values.
         *
         * @relatedalso operator<<(uint32_t)
         * @relatedalso operator<<=(uint32_t)
         * @relatedalso operator>>=(uint32_t)
         * @relatedalso shiftRightLogical(uint32_t)
         * @relatedalso shiftLeft<uint32_t>()
         * @relatedalso shiftRightArithmetic<uint32_t>()
         * @relatedalso shiftRightLogical<uint32_t>()
         */
        [[nodiscard]] constexpr Simd256 operator>>(uint32_t count) const noexcept;


        /**
         * @brief Perform a arithmetic/logical(type dependent) right shift on this register by @p count.
         *
         * @warning If @p count is known at compile time then it is recommended to use
         *          @ref shiftRightArithmetic<uint32_t> as it is faster.
         *
         * @return A reference to this register.
         *
         * @relatedalso operator<<(uint32_t)
         * @relatedalso operator<<=(uint32_t)
         * @relatedalso operator>>(uint32_t)
         * @relatedalso shiftRightLogical(uint32_t)
         * @relatedalso shiftLeft<uint32_t>()
         * @relatedalso shiftRightArithmetic<uint32_t>()
         * @relatedalso shiftRightLogical<uint32_t>()
         */
        constexpr Simd256& operator>>=(uint32_t count) noexcept;


        /**
         * @brief Perform a logical right shift (zero extension) on this register and return a new register.
         *
         * @warning If @p count is known at compile time then it is recommended to use
         *          @ref shiftRightLogical<uint32_t> as it is faster.
         *
         * @return A new 256-bit register with shifted values.
         *
         * @relatedalso operator<<(uint32_t)
         * @relatedalso operator<<=(uint32_t)
         * @relatedalso operator>>(uint32_t)
         * @relatedalso operator>>=(uint32_t)
         * @relatedalso shiftLeft<uint32_t>()
         * @relatedalso shiftRightArithmetic<uint32_t>()
         * @relatedalso shiftRightLogical<uint32_t>()
         */
        [[nodiscard]] constexpr Simd256 shiftRightLogical(uint32_t count) const noexcept;


        //     /**
        //      * @brief Perform a logical left shift on this register by a compile time constant, @p Count.
        //      *
        //      * @tparam Count The shift amount.
        //      *
        //      * @relatedalso operator<<(uint32_t)
        //      * @relatedalso operator<<=(uint32_t)
        //      * @relatedalso operator>>(uint32_t)
        //      * @relatedalso operator>>=(uint32_t)
        //      * @relatedalso shiftRightLogical(uint32_t)
        //      * @relatedalso shiftRightArithmetic<uint32_t>()
        //      * @relatedalso shiftRightLogical<uint32_t>()
        //      */
        //     template <uint32_t Count>
        //     [[nodiscard]] constexpr Simd256 shiftLeft() const noexcept;
        //
        //
        //     /**
        //      * @brief Perform a arithmetic right shift on this register by a compile time constant, @p Count.
        //      *
        //      * @tparam Count The shift amount.
        //      *
        //      * @relatedalso operator<<(uint32_t)
        //      * @relatedalso operator<<=(uint32_t)
        //      * @relatedalso operator>>(uint32_t)
        //      * @relatedalso operator>>=(uint32_t)
        //      * @relatedalso shiftRightLogical(uint32_t)
        //      * @relatedalso shiftLeft<uint32_t>()
        //      * @relatedalso shiftRightLogical<uint32_t>()
        //      */
        //     template <uint32_t Count>
        //     [[nodiscard]] constexpr Simd256 shiftRightArithmetic() const noexcept;
        //
        //
        //     /**
        //      * @brief Perform a logical right shift on this register by a compile time constant, @p Count.
        //      *
        //      * @tparam Count The shift amount.
        //      *
        //      * @relatedalso operator<<(uint32_t)
        //      * @relatedalso operator<<=(uint32_t)
        //      * @relatedalso operator>>(uint32_t)
        //      * @relatedalso operator>>=(uint32_t)
        //      * @relatedalso shiftRightLogical(uint32_t)
        //      * @relatedalso shiftLeft<uint32_t>()
        //      * @relatedalso shiftRightLogical<uint32_t>()
        //      */
        //     template <uint32_t Count>
        //     [[nodiscard]] constexpr Simd256 shiftRightLogical() const noexcept;
        //
        //
        //     ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        //     ///   MASKING/BLENDING
        //     ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        //
        //     /**
        //      * @brief Create a mask for register value blending.
        //      *
        //      * @tparam Mask The bool mask to be converted. The first bool translates to the lower n-bits.
        //      *              Number of Mask arguments must be between 2 and @p Lane and must be a power of 2.
        //      *
        //      * @code
        //      * // float x 8(lane) mask.
        //      * const Simd256_t<float, 8> reg{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f };
        //      * const auto mask = reg.makeBlendMask<true, false, true, false>();
        //      * // 0b00000000111111110000000011111111 or 0x00FF00FF
        //      * const auto mask = reg.makeBlendMask<true, false, true, true>();
        //      * // 0b11111111111111110000000011111111 or 0xFFFF00FF
        //      * @endcode
        //      *
        //      * @return A 32-bit integral mask usable across Simd256 const blending.
        //      */
        //     template <bool... Mask>
        //         requires(std::has_single_bit(sizeof...(Mask)) && sizeof...(Mask) >= 2 && sizeof...(Mask) <= Lane)
        //     static constexpr BlendMask32_t makeBlendMask() noexcept
        //     { return simd::makeBlendMask32<MaxLaneCount, Mask...>(); }
        //
        //
        //     /**
        //      * @brief Selectively blend values from this register and @p other using the @p mask.
        //      *
        //      * @code
        //      * // Masking sample
        //      * this  -> 0x ff 23 15 81
        //      * other -> 0x 32 3f ed 55
        //      * mask  -> 0x ff 00 ff 00
        //      * ret   -> 0x 32 23 ed 81
        //      * @endcode
        //      *
        //      * @param other The register whose values are selected when mask is 0b11..11 or 0xf..f.
        //      * @param mask  The mask to use for blending.
        //      *
        //      * @return Return a new register with blended values.
        //      */
        //     [[nodiscard]] constexpr Simd256 blend(Simd256 other, Simd256 mask) const noexcept;
        //
        //
        //     /**
        //      * @brief Selectively blend values from this register and @p other using the compile-time @p Mask.
        //      * @tparam Mask The mask to use for blending.
        //      *              Use @ref flcn::makeBlendMask32<...>() to create the mask.
        //      *              `true` selects values from the other register and `false` from this register.
        //      * @note   Even though the mask is uint32_t, only lower 8-bit will be considered
        //      *
        //      * @code
        //      * // Masking sample
        //      * this  -> 0x ff 23 15 81
        //      * other -> 0x 32 3f ed 55
        //      * mask  -> 0x ff 00 ff 00
        //      * ret   -> 0x 32 23 ed 81
        //      *
        //      * // Usage
        //      * const flcn::Simd256_t<float, 8> reg1{1.0f, 2.0f, 3.0f, 4.0f, 12.0f, 13.0f, 14.0f, 15.0f};
        //      * const flcn::Simd256_t<float, 8> reg2{8.0f, 9.0f, 10.0f, 11.0f, 5.0f, 6.0f, 7.0f, 8.0f};
        //      * constexpr auto mask = flcn::makeBlendMask32<true, false, false, true, true, true, false, false>();
        //      * const auto blended = reg1.template blend<mask>(reg2); //
        //      {8.0f, 2.0f, 3.0f, 11.0f, 5.0f, 6.0f, 14.0f, 15.0f}
        //      * @endcode
        //      *
        //      * @param other The register whose values are selected when mask is 0b11..11 or 0xf..f.
        //      *
        //      * @return Return a new register with blended values.
        //      */
        //     template <BlendMask32_t Mask>
        //     [[nodiscard]] constexpr Simd256 blend(Simd256 other) const noexcept;
        //
        //
        //     /**
        //      * Shuffle the values as per given index.
        //      *
        //      * @tparam ShuffleIndex The indices to use for shuffling. Only accepts values from 0 to Lane - 1.
        //      *                      Must be specified from lower index to higher index,
        //      *                      i.e, <0, 1, 2, 3> returns a copy of the same register.
        //      *
        //      * @return A new Simd register with shuffled values.
        //      */
        //     template <uint8_t... ShuffleIndex>
        //     [[nodiscard]] constexpr Simd256 shuffle() const noexcept;
        //


        /// @brief Get the internal register used by Simd256.
        [[nodiscard]] FALCON_INLINE constexpr simd::internal::Simd256Register_t<CURRENT_SIMD_BACKEND, DataType, Lane>
        naive() const noexcept
        { return _reg; }


        /// @brief Get the internal register used by Simd256.
        [[nodiscard]] FALCON_INLINE constexpr simd::internal::Simd256Register_t<CURRENT_SIMD_BACKEND, DataType, Lane>
        operator*() const noexcept
        { return _reg; }



        //     ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        //     ///       UTILITIES
        //     ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        //
        //
        //     /// @brief Get the minimum value from this register.
        //     [[nodiscard]] constexpr DataType horizontalMin() const noexcept;
        //
        //
        //     /// @brief Get the maximum value from this register.
        //     [[nodiscard]] constexpr DataType horizontalMax() const noexcept;
        //
        //     /**
        //      * @brief Compute the absolute value of each entry in this register.
        //      * @note For unsigned types the value will not be affected.
        //      *
        //      * @return A Simd256 register with absolute values.
        //      */
        //     [[nodiscard]] constexpr Simd256 abs() const noexcept;
        //
        //
        //     /**
        //      * @brief Compute the square root value of each entry in this register.
        //      *
        //      * @note For integral square roots less than zero, this will generate a zero value.
        //      *       For floating-point number, the function follow standard behavior of return a NaN for negatives.
        //      *
        //      * @return A Simd256 register with square root of values, rounded to the same target type.
        //      */
        //     [[nodiscard]] constexpr Simd256 sqrt() const noexcept;
        //
        //
        //     /// @brief Get a mask with the Nan status of each Lane of elements.
        //     /// @note Integrals always return a zero register.
        //     [[nodiscard]] constexpr Simd256 hasNan() const noexcept;
        //
        //
        //     /// @brief Get a mask with the Inf status of each Lane of elements.
        //     /// @note Integrals always return a zero register.
        //     [[nodiscard]] constexpr Simd256 hasInf() const noexcept;


    private:
        static constexpr auto Max128BitLaneCount = 128 / (sizeof(DataType) * 8);
        static_assert(Lane > Max128BitLaneCount, "Payload fits in 128-bits. Use Simd128 to directly.");

        /// TODO: REMOVE IF NOT REQUIRED
        static constexpr auto LowerLaneCount = Max128BitLaneCount;
        static constexpr auto UpperLaneCount = (Lane - Max128BitLaneCount > 0) ? (Lane - Max128BitLaneCount) : 0;

        simd::internal::Simd256Register_t<CURRENT_SIMD_BACKEND, DataType, Lane> _reg;
    };


} // namespace flcn


// --- THIS SHOULD BE INCLUDED FIRST as the .inl files use functions declared in this header.
#include "CustomX86Intrin.inl"
#include "Simd256X86Math.h"
// ------
#include "Simd256AVX.inl"
