#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"
#include "parser.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout<<"missing filename\n";
        return 1;
    }

    std::ifstream file{ argv[1]};

    if (!file) {
        std::cerr <<"cannot read file " << argv[1] <<'\n';
        return 1;
    }

   
    std::string source{};
    std::string line;
    if (file.is_open()) {
        while(std::getline(file, line)) {
            source += line + '\n';
        }
        file.close();
    } else {
        std::cerr << "unable to open file\n";
        return 1;
    }
 
    Lexer lex{source};
    Parser parser{lex};

    parser.program();
    std::cout << "parsing completed\n";

   }
