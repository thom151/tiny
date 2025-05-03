#include "lexer.h"
#include "token.h"
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>

class Parser {
    Lexer mLexer; 
    Token mCurrToken{};
    Token mPeekToken{};
    std::set<std::string> mSymbols{};
    std::set<std::string> mLabelsDeclared{};
    std::set<std::string> mLabelGotoed{};

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
        std::cerr << "Parsing error: " << message << '\n';
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
            //if label exsits, return error
            if (mLabelsDeclared.find(mCurrToken.getText())!= mLabelsDeclared.end()) {
                abort("label current exists" + mCurrToken.getText());
            }

            mLabelsDeclared.insert(mCurrToken.getText());
            match(IDENT);    

        } else if (checkToken(GOTO)) {
            std::cout<<"STATEMENT-GOTO\n";
            //inset labels (currToken) in the mLabelsGotoed (can occur multiple times)
            nextToken(); 
            mLabelGotoed.insert(mCurrToken.getText());
            match(IDENT);    

        } else if (checkToken(LET)) {
            std::cout<<"STATEMENT-LET\n";
            nextToken();
            //if currToken does not exist, insert
            if (mSymbols.find(mCurrToken.getText()) == mSymbols.end()) {
                    mSymbols.insert(mCurrToken.getText());
            }
            match(IDENT);
            match(EQ);
            expression();

        } else if (checkToken(INPUT)) {
            std::cout<<"STATEMENT-INPUT\n";
            nextToken();
            //if currToken does not exist, insert
            if (mSymbols.find(mCurrToken.getText()) == mSymbols.end()) {
                    mSymbols.insert(mCurrToken.getText());
            }
            match(IDENT);   
        } else {
            abort("invalid statement at " + mCurrToken.getText());
        }
        nl();
    }

    void expression() {
        std::cout<<"EXPRESSION\n";
        term(); // 1
        while(checkToken(PLUS) ||checkToken( MINUS)) {
            nextToken();
            term();
        }
        
        return;
    }

    void term() {
        std::cout<<"TERM\n";
        unary(); 

        while (checkToken(ASTERISK) || checkToken(SLASH)) {
            nextToken();
            unary(); // 2
            
        }
    }

    void unary() {
        std::cout<<"UNARY\n"; 

        if (checkToken(PLUS) || checkToken(MINUS)) {
            nextToken();
        }
        primary(); 
    }

    void primary() {
        std::cout<<"PRIMARY (" << mCurrToken.getText() << ")\n"; 

        if (checkToken(NUMBER)) {
            nextToken();
        } else if (checkToken(IDENT)) {
            if(mSymbols.find(mCurrToken.getText()) == mSymbols.end()) {
                abort("variable has not been declared: " + mCurrToken.getText());
            }
    
            nextToken();
        } else {
            abort("unexpected token" + mCurrToken.getText());
        }
    }
    
    void comparison() {
        std::cout<<"COMPARISON\n";
        expression();

        if (isComparisonOperator()) {
            nextToken();
            expression();
        } else {
            abort("expected comparison operator");
        }

        while (isComparisonOperator()) {
            nextToken();
            expression();
        }
        return;
    }

    bool isComparisonOperator() {
        return  checkToken(GT)   ||
                checkToken(GTEQ) ||
                checkToken(LT)   ||
                checkToken(LTEQ) ||
                checkToken(EQEQ) ||
                checkToken(NOTEQ);
    }

    void nl() {
        std::cout << "NEWLINE" << '\n';

        match(NEWLINE);
        while (checkToken(NEWLINE)) {
            nextToken();
        }
    }
};
