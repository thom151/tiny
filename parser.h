#include "lexer.h"
#include <cstdlib>
#include <iostream>

class Parser {
    Lexer mLexer; 
    Token mCurrToken{};
    Token mPeekToken{};

public:

    Parser ( Lexer lexer)
    : mLexer{lexer} {
            nextToken();
            nextToken();
    }

    bool checkToken( TokenType kind) {
        return kind == mCurrToken.getKind();
    }

    bool checkPeek( TokenType kind) {
        return kind == mPeekToken.getKind();
    }

    void nextToken() {
        mCurrToken = mPeekToken;
        mPeekToken = mLexer.getToken();
    }

    void match(TokenType kind) {
        if (!checkToken(kind)) {
            abort("Expected" + getKindName(kind) + ", got" + getKindName(mCurrToken.getKind()));
        }
        nextToken();
    }

    void abort(std::string message) {
        std::cerr << "Parsing error" << message << '\n';
        std::exit(1);
    }


    void program() {
        std::cout<<"PROGRAM\n";
        while (!checkToken(ENDOFFILE)) {
            statement();
        }
    }

    void statement() {
        if (checkToken(PRINT)) {
            std::cout <<"STATEMENT-PRINT"<<'\n';
            nextToken();
        }

        if (checkToken(STRING)) {
            nextToken();
        } else {
            expression();
        }


        nl();
    }

    void expression() {
        return;
    }

    void nl() {
        std::cout << "NEWLINE" << '\n';

        match(NEWLINE);
        while (checkToken(NEWLINE)) {
            nextToken();
        }
    }
};
