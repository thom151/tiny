#include <iostream>
#include "lexer.h"


int main() {

    Lexer lex{"LET foobar = 123"};

    while (lex.peek() != '\0') {
        std::cout <<lex.getCurrChar()<<'\n';
        lex.nextChar();
    }
}
