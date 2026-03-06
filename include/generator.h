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
                if(n->tok.type == INT) return std::to_string(variant2int(n->tok.value));
                if(n->tok.type == DOUBLE) return std::to_string(variant2double(n->tok.value));
                if(n->tok.type == STRING) return variant2string(n->tok.value);
                if(n->tok.type == TRUE || n->tok.type == FALSE) return std::to_string(variant2bool(n->tok.value));
                if(n->tok.type == NULL_) return variant2string(n->tok.value);
                if(n->tok.type == ID) return variant2string(n->tok.value);
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
                return variant2string(n->id.value) + (value.empty() ? "" : "=" + value);
            }
            case ast_type::DEFINEVAR: {
                auto n = static_cast<AssignmentNodeExpr*>(node.get());
                std::string type;
                if(n->type_==INT_TYPE) type = " long long ";
                if(n->type_==DOUBLE_TYPE) type = " double ";
                if(n->type_==STRING_TYPE) type = " std::string ";
                if(n->type_==BOOL_TYPE) type = " bool ";
                if(n->type_==UNSIGNED_TYPE) type = " unsigned long long ";
                std::string val = n->val ? genCode(n->val) : "";
                return type + variant2string(n->id.value) + (val.empty() ? "" : "=" + val);
            }
            case ast_type::UNARY: {
                auto n = static_cast<UnaryNode*>(node.get());
                if(n->sign == MINUS) return "-" + genCode(n->left);
                return genCode(n->left);
            }
            default:
                return "";
        }
    } 

    std::string generate(std::vector<astptr> &nodes) {
        std::string res = "#include <iostream>\nint main() {\n";
        for(auto &x : nodes) {
            res += genCode(x) + ';';
            res += '\n';
        }
        res += "return 0;\n}\n";
        return res;
    }
};