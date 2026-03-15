#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "common.h"
#include "lexer.h"

using symbol = struct symbol {
    token_type type;
    token_value value;
    bool is_const=false;
    u64 size=0;
    bool is_array=false;
};

extern std::vector<std::unordered_map<std::string, symbol>> table;

token_value search_value(const std::string &name);

symbol search(const std::string &name);

token_type search_type(const std::string &name);

token_type search_type_scope(const std::string &name, unsigned int lvl);


void insert(const std::string &name,token_type type, token_value val, bool is_const=false, u64 size=1, bool is_array=false);
void insert_top(const std::string &name,token_type type, token_value val,bool is_const=false, u64 size=1, bool is_array=false);

bool exist(const std::string &name);

bool exist_in_scope(const std::string &name, unsigned int lvl);