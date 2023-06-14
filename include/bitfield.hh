/* SPDX-License-Identifier: MIT */
#ifndef BITFIELD_H_
#define BITFIELD_H_

/*
** Heavily borrowed from Kacper Kowalski's portable bitfield implementation
** https://github.com/KKoovalsky/PortableBitfields
**
** Uses classic bitfield math instead of array of fields
*/

#include <array>

namespace zutil {

template <auto Id, unsigned MSB, unsigned LSB = MSB>
struct Field {
    static inline constexpr auto id { Id };
    static inline constexpr auto mask { ((1UL << ((MSB + 1) - LSB)) - 1) << LSB };
    static inline constexpr auto lsb { mask & ~(mask - 1) };
};

template <typename Underlying, typename... Fields>
class Bitfield {
public:
    constexpr Bitfield() = default;
    constexpr Bitfield(Underlying value)
        : value(value) {};

    template <auto Field>
    constexpr Underlying get() noexcept
    {
        constexpr auto idx { field_index<Field>() };
        constexpr auto mask { field_masks[idx] };
        constexpr auto lsb { field_lsbs[idx] };
        auto v { value & mask };
        return v / lsb;
    }

    template <auto Field>
    constexpr void set(Underlying val) noexcept
    {
        constexpr auto idx { field_index<Field>() };
        constexpr auto mask { field_masks[idx] };
        constexpr auto lsb { field_lsbs[idx] };
        auto v { value & ~mask };
        value = v | ((val * lsb) & mask);
    }

    constexpr Underlying val() noexcept { return value; };

    operator Underlying() const { return value; }

private:
    template <class InputIt, class T>
    static constexpr InputIt find(InputIt first, InputIt last, const T& value)
    {
        for (; first != last; ++first) {
            if (*first == value) {
                return first;
            }
        }
        return last;
    }

    static inline constexpr bool has_duplicates()
    {
        auto beg { std::begin(field_ids) }, end { std::end(field_ids) };

        for (auto it { beg }; it != end; ++it) {
            auto match_it { find(std::next(it), end, *it) };
            if (match_it != end)
                return true;
        }

        return false;
    }

    template <auto Field>
    static inline constexpr auto field_index() noexcept
    {
        constexpr auto it { find(std::begin(field_ids), std::end(field_ids), Field) };
        static_assert(it != std::end(field_ids), "Field ID not found");
        return static_cast<unsigned>(std::distance(std::begin(field_ids), it));
    }

    static inline constexpr std::array field_ids { Fields::id... };
    static inline constexpr std::array field_masks { Fields::mask... };
    static inline constexpr std::array field_lsbs { Fields::lsb... };

    static_assert(std::is_integral<Underlying>::value, "UnderlyingType must be an integral type");
    static_assert(not has_duplicates(), "Field IDs must not duplicate");

    Underlying value;
};

}

#endif // BITFIELD_H_
