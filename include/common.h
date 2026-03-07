#pragma once

#include "lexer.h"
#include <limits>

typedef unsigned long long u64;
typedef long long i64;
typedef double f64;
typedef unsigned char u8;

inline std::string variant2string(token_value &val) {
    if(const std::string* s = std::get_if<std::string>(&val)) {
        return *s;
    }
    return "error";
}

template<typename T>
inline long long variant2int(token_value &val) {
    return std::get<T>(val);
}

inline long long variant2double(token_value &val) {
    return std::get<double>(val);
}

inline long long variant2bool(token_value &val) {
    return std::get<bool>(val);
}

template<typename T>
bool fits(long long v) {
    return v >= std::numeric_limits<T>::min() &&
           v <= std::numeric_limits<T>::max();
}

inline bool is_it_value(token a) {
    if(a.type >= 13 && a.type <= 22) return true;
    return false;
}