#pragma once

#include "lexer.h"

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

inline long long variant2int(token_value &val) {
    return std::get<long long>(val);
}

inline long long variant2double(token_value &val) {
    return std::get<double>(val);
}

inline long long variant2bool(token_value &val) {
    return std::get<bool>(val);
}