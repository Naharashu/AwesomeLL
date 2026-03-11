#pragma once

#include "ast.h"
#include "common.h"
#include "lexer.h"
#include "parser.h"
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/*
if (x->kind == ast_type::MODULE) {
        auto n = static_cast<ModuleNode *>(x.get());
        lexer lex;
        std::string code;
        std::string line;
        std::ifstream mod(n->name.c_str());
        while (std::getline(mod, line)) {
          code += line + '\n';
        }
        mod.close();
        std::vector<token> toks = lex.lex(code);
        parser parser_(toks);
        std::vector<astptr> res = parser_.parse();
        for (auto &y : res) {
          std::string yc = genCode(y);
          if (yc.empty())
            continue;
          if (y->kind != ast_type::MODULE && y->kind != ast_type::BLOCK &&
              y->kind != ast_type::IF)
            cpp_code << yc + ';';
          else
            cpp_code << yc;
          cpp_code << '\n';
        }
        continue;
      }
*/

class generator {
public:
  int indent = 0;

  std::string pad() { return std::string(indent * 4, ' '); }

  std::ostringstream cpp_code;
  std::string header;
  std::string gencode(astptr &node) {
    return node->gen(*this);
  }

  std::string generate(std::vector<astptr> &nodes) {
    if(header.find("<iostream>\n")==std::string::npos) { 
      header += "#include <iostream>\n";
    }
    if(header.find("<cstdint>")==std::string::npos) {
      header += "#include <cstdint>\n";
    }
    for (auto &x : nodes) {
      std::string c = gencode(x);
      if (c.empty())
        continue;

      if (x->kind != ast_type::MODULE && x->kind != ast_type::BLOCK &&
          x->kind != ast_type::IF)
        cpp_code << c + ';';

      else
        cpp_code << c;
      cpp_code << '\n';
    }
    return header + cpp_code.str();
  }
};
