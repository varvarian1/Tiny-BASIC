#pragma once

#include <array>

namespace lut {
    template<size_t N>
    static constexpr auto createLookupTable(const char(&chars)[N]) {
        std::array<bool, 256> table{};    
        for (size_t i = 0; i < N - 1; ++i) {
            table[static_cast<unsigned char>(chars[i])] = true;
        }
        return table;
    };

    constexpr auto Binary = createLookupTable("01");
    constexpr auto Numeric = createLookupTable("0123456789");
    constexpr auto RealNumeric = createLookupTable(".0123456789");
    constexpr auto Hex = createLookupTable("0123456789abcdefABCDEF");
    constexpr auto Identifier = createLookupTable("abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789");
    constexpr auto Operator = createLookupTable("!$%^&=#@?|`\\<>~");
    constexpr auto Whitespace = createLookupTable(" \t\n\r\v\f");
};
