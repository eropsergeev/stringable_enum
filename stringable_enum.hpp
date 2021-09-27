#ifndef __STINGABLE_ENUM__HPP__
#define __STINGABLE_ENUM__HPP__

#include <array>
#include <string_view>
#include <cinttypes>
#include <limits>

namespace stringable_enum {

template<size_t N>
struct EnumOptions {
    struct Seg {
        uint16_t l, r;
        int v;
    };
    std::array<Seg, N> segs{};
    uint16_t count = 0;
    std::array<char, N> data{};
    consteval EnumOptions(const char (&s)[N]) {
        static_assert(N <= (size_t) std::numeric_limits<uint16_t>::max());
        uint16_t pos = 0;
        bool in_name = 0, in_value = 0;
        uint16_t name_start = 0;
        int val = 0;
        bool minus = 0;
        while (s[pos]) {
            data[pos] = s[pos];
            if (('a' <= s[pos] && s[pos] <= 'z')
                || ('A' <= s[pos] && s[pos] <= 'Z')
                || s[pos] == '$' || s[pos] == '_'
                || (in_name && '0' <= s[pos] && s[pos] <= '9'))
            {
                if (!in_name)
                    name_start = pos;
                in_name = 1;
            } else {
                if (in_name) {
                    segs[count++] = Seg{name_start, pos, val++};
                }
                in_name = 0;
                if (in_value && '0' <= s[pos] && s[pos] <= '9') {
                    val *= 10;
                    if (minus)
                        val -= s[pos] - '0';
                    else
                        val += s[pos] - '0';
                } else if (in_value && s[pos] == '-') {
                    minus = 1;
                }
                if (s[pos] == '=') {
                    in_value = 1;
                    minus = 0;
                    val = 0;
                } else if (s[pos] == ',') {
                    segs[count - 1].v = val;
                    in_value = 0;
                }
            }
            ++pos;
        }
        if (in_name) {
            segs[count++] = Seg{name_start, pos, val++};
        } else if (in_value) {
            segs[count - 1].v = val;
        }
    }
};

template<EnumOptions opts>
consteval auto operator ""_enum_to_string_func() {
    return [](auto e) {
        for (uint16_t i = 0; i < opts.count; ++i) {
            auto [l, r, v] = opts.segs[i];
            if (e == static_cast<decltype(e)>(v))
                return std::string_view(opts.data.begin() + l, opts.data.begin() + r);
        }
        return std::string_view("");
    };
}

}; // namespace stringable_enum

#define ENUM(Name, ...) enum Name { __VA_ARGS__ }; auto to_string(Name e) { \
    using namespace stringable_enum; \
    return (#__VA_ARGS__ ""_enum_to_string_func)(e); \
}

#define ENUM_CLASS(Name, ...) enum class Name { __VA_ARGS__ }; auto to_string(Name e) { \
    using namespace stringable_enum; \
    return (#__VA_ARGS__ ""_enum_to_string_func)(e); \
}

#endif