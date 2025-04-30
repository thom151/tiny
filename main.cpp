#include <iostream>
#include "lexer.h"


int main() {

    Lexer lex{"+- */"};


    Token token = lex.getToken();
    while (token.getKind() != ENDOFFILE) {
        std::cout <<"KIND: "<< token.getKind() <<'\n';
        token = lex.getToken();
    }
}
