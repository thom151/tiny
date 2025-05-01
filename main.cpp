#include <iostream>
#include "lexer.h"


int main() {

    Lexer lex{"IF+-123 foo*THEN/"};


    Token token = lex.getToken();
    while (token.getKind() != ENDOFFILE) {
        std::cout <<"KIND: "<< token.getKind() << " TEXT: "<< token.getText()<<'\n';
        token = lex.getToken();
    }
}
