#pragma once

#include "ast.h"
#include "lexer.h"
#include <memory>
#include <string>
#include <vector>
#include "common.h"

class generator {
    public:
    std::string genCode(astptr &node) {
        switch(node->kind) {
            case ast_type::JUSTNODE: {
                auto n = static_cast<Node*>(node.get());
                if(n->tok.type == BYTE) return std::to_string((char)variant2int<long long>(n->tok.value));
                if(n->tok.type == WORD) return std::to_string((short)variant2int<long long>(n->tok.value));
                if(n->tok.type == INT) return std::to_string((int)variant2int<long long>(n->tok.value));
                if(n->tok.type == LONG) return std::to_string(variant2int<long long>(n->tok.value));
                if(n->tok.type == FLOAT) return std::to_string((float)variant2double(n->tok.value));
                if(n->tok.type == DOUBLE) return std::to_string(variant2double(n->tok.value));
                if(n->tok.type == STRING) return "\"" + variant2string(n->tok.value) + "\"";
                if(n->tok.type == TRUE || n->tok.type == FALSE) return std::to_string(variant2bool(n->tok.value));
                if(n->tok.type == NULL_) return variant2string(n->tok.value);
                if(n->tok.type == ID) return variant2string(n->tok.value);
                break;
            }
            case ast_type::BINARY: {
                auto n = static_cast<BinaryNode*>(node.get());
                std::string op;
                if(n->op==PLUS) op = " + ";
                if(n->op==MINUS) op = " - ";
                if(n->op==STAR) op = " * ";
                if(n->op==SLASH) op = " / ";
                return '(' + genCode(n->left) + op + genCode(n->right) + ')';
            }
            case ast_type::ASSIGN: {
                auto n = static_cast<AssignmentNode*>(node.get());
                std::string value = n->val ? genCode(n->val) : "";
                return " " + variant2string(n->id.value) + (value.empty() ? "" : "=" + value);
            }
            case ast_type::DEFINEVAR: {
                auto n = static_cast<AssignmentNodeExpr*>(node.get());
                std::string type;
                std::string nullval = "0";
                if(n->type_==BYTE_TYPE) type = " int8_t ";
                if(n->type_==WORD_TYPE) type = " int16_t ";
                if(n->type_==INT_TYPE) type = " int32_t ";
                if(n->type_==LONG_TYPE) type = " int64_t ";
                if(n->type_==FLOAT_TYPE) type = " float ";
                if(n->type_==DOUBLE_TYPE) type = " double ";
                if(n->type_==STRING_TYPE) {
                    type = " std::string ";
                    nullval = "\"\"";
                }
                if(n->type_==BOOL_TYPE) type = " bool ";
                if(n->type_==UNSIGNED_8_TYPE) type = " uint8_t ";
                if(n->type_==UNSIGNED_16_TYPE) type = " uint16_t ";
                if(n->type_==UNSIGNED_32_TYPE) type = " uint32_t ";
                if(n->type_==UNSIGNED_64_TYPE) type = " uint64_t ";
                std::string val = n->val ? genCode(n->val) : "";
                return type + variant2string(n->id.value) + (val.empty() ? "=" + nullval : "=" + val);
            }
            case ast_type::UNARY: {
                auto n = static_cast<UnaryNode*>(node.get());
                if(n->sign == MINUS) return "-" + genCode(n->left);
                return genCode(n->left);
            }
            case ast_type::FuncCall: {
                auto n = static_cast<FuncCallNode*>(node.get());
                std::string args;
                if(variant2string(n->id.value) == "print") {
                    args = "std::cout << ";
                    for(auto &x : n->args) {
                        args += genCode(x);
                        args += " << ";
                    }
                    args += "std::endl;";
                    return args;
                }
                for(auto &x : n->args) {
                    args += genCode(x);
                    args += " , ";
                }
                args.erase(args.length() - 2);
                return variant2string(n->id.value) + '(' + args + ')';
            }
            default:
                return "";
        }
        return "";
    } 

    std::string generate(std::vector<astptr> &nodes) {
        std::string res = "#include <iostream>\n"
                        "#include <cmath>\n"
                        "#include <cstdint>\n"
                        "int main() {\n";
        for(auto &x : nodes) {
            res += genCode(x) + ';';
            res += '\n';
        }
        res += "return 0;\n}\n";
        return res;
    }
};