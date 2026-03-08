#include "include/ast.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/generator.h"
#include <cstdlib>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) { 
    lexer lex;
    std::string code;
    code.clear();
    if(argc<2) {
        std::cerr << "Usage: flame [file.flame] -o [DEFAULT=out]\n";
        return 1; 
    }
    std::string out_name = "out";
    std::string line;
    if(argc>=4) {
        out_name = argv[3];
    }
    std::ifstream file(argv[1]);
    while(std::getline(file, line)) {
        code += line + '\n';
    }
    file.close();
    std::vector<token> toks = lex.lex(code);
    parser parser_(toks);
    for(auto x : toks) {
        std::cout << x.type << ' ';
    }
    std::cout << '\n';
    std::vector<astptr> res = parser_.parse();
    generator gen;
    std::string code_ = gen.generate(res);
    std::ofstream out("temp_flame.cpp", std::ios::out | std::ios::binary);
    out.write(code_.c_str(), code_.size());
    out.close();
    std::string output = "g++ temp_flame.cpp -o " + out_name; //" && rm -f temp.cpp";
    system(output.c_str());
    //std::cout << code_ << std::endl;
    return 0; 
}
