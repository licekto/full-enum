#include <string>
#include <cstring>
#include <optional>
#include <iostream>
#include <boost/preprocessor.hpp>

#define __ENUMERATOR_TO_STRING__(r, data, elem) \
    BOOST_PP_STRINGIZE(elem),

#define DEF_ENUM(__NAME__, ...)                                                                         \
class __NAME__ {                                                                                        \
public:                                                                                                 \
    enum _enumerated { __VA_ARGS__ };                                                                   \
                                                                                                        \
    __NAME__(_enumerated val) : _value(val) {}                                                          \
    operator _enumerated() const { return _value; }                                                     \
                                                                                                        \
    size_t size() const { return BOOST_PP_VARIADIC_SIZE(__VA_ARGS__); }                                 \
    const char * toString() const {                                                                     \
        assert(_value < BOOST_PP_VARIADIC_SIZE(__VA_ARGS__));                                           \
        return _names[static_cast<size_t>(_value)];                                                     \
    }                                                                                                   \
    static std::optional<_enumerated> fromString(const char * const enumStr) {                          \
        for (size_t i = 0; i < BOOST_PP_VARIADIC_SIZE(__VA_ARGS__); ++i) {                              \
            if (!std::strcmp(enumStr, _names[i])) {                                                     \
                return static_cast<_enumerated>(i);                                                     \
            }                                                                                           \
        }                                                                                               \
        return std::nullopt;                                                                            \
    }                                                                                                   \
private:                                                                                                \
    _enumerated _value;                                                                                 \
    inline static const char * const _names[] = {                                                       \
        BOOST_PP_SEQ_FOR_EACH(__ENUMERATOR_TO_STRING__, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) };    \
};                                                                                                      \
std::ostream &operator<<(std::ostream &os, const __NAME__ e) {                                          \
    return os << e.toString();                                                                          \
}                                                                                                       \
std::istream &operator>>(std::istream &is, __NAME__ &e) {                                               \
    std::string enumStr;                                                                                \
    is >> enumStr;                                                                                      \
    auto val = __NAME__::fromString(enumStr.c_str());                                                   \
    if (val.has_value()) {                                                                              \
        e = val.value();                                                                                \
    }                                                                                                   \
    /* Throw an exception */                                                                            \
    return is;                                                                                          \
}
