#include "include/ast.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/generator.h"
#include <fstream>

int main() { 
    lexer lex;
    std::string code = "i32 x=1+3-5;\n u16 a = 3; print(a)";
    std::vector<token> toks = lex.lex(code);
    parser parser_(toks);
    for(auto x : toks) {
        std::cout << x.type << ' ';
    }
    std::cout << '\n';
    std::vector<astptr> res = parser_.parse();
    generator gen;
    std::string code_ = gen.generate(res);
    std::ofstream out("temp.cpp", std::ios::out | std::ios::binary);
    out.write(code_.c_str(), code_.size());
    out.close();
    //std::cout << code_ << std::endl;
    return 0; 
}
