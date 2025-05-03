#include "lexer.h"
#include "token.h"
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

    //check if the expected token (argument) is the current Token
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

        while (checkToken(NEWLINE)) {
            nextToken();

        }
        while (!checkToken(ENDOFFILE)) {
            statement();
        }
    }

    void statement() {
        if (checkToken(PRINT)) {
            std::cout <<"STATEMENT-PRINT"<<'\n';
            nextToken();
        

            if (checkToken(STRING)) {
                nextToken();
            } else {
                 expression();
             }
        } else if (checkToken(IF)) {
            std::cout<<"STATEMENT-IF\n";
            nextToken();//get the next token
            comparison();//make sure that the next token can be parsed by the comparison
            match(THEN);
            nl();

            while (!checkToken(ENDIF)){
                statement();
            }

            match(ENDIF);
        } else if(checkToken(WHILE)) {
            std::cout<<"STATEMENT-WHILE\n";
            nextToken();
            comparison();
            match(REPEAT);
            nl();
            while(!checkToken(ENDWHILE)) {
                statement();
            }

            match(ENDWHILE);
        } else if (checkToken(LABEL)) {
            std::cout<<"STATEMENT-LABEL\n";
            nextToken();
            match(IDENT);    
        } else if (checkToken(GOTO)) {
            std::cout<<"STATEMENT-GOTO\n";
            nextToken();
            match(IDENT);    
        } else if (checkToken(LET)) {
            std::cout<<"STATEMENT-LET\n";
            nextToken();
            match(IDENT);
            match(EQ);
            expression();
        } else if (checkToken(INPUT)) {
            std::cout<<"STATEMENT-INPUT\n";
            nextToken();
            match(IDENT);   
        } else {
            abort("invalid statement at" + getKindName(mCurrToken.getKind()));
        }




        nl();
    }

    void expression() {
        return;
    }
    
    void comparison() {
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
