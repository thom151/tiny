#ifndef TOKEN_H
#define TOKEN_H

#include <cstddef>
#include <ostream>
#include <string>

enum TokenType {
    ENDOFFILE = -1,
    NEWLINE = 0,
    NUMBER = 1,
    IDENT = 2,
    STRING = 3,

    //KEYWORDS
    LABEL = 101,
    GOTO = 102,
    PRINT = 103,
    INPUT = 104,
    LET = 105,
    IF = 106,
    THEN = 107,
    ENDIF = 108,
    WHILE = 109,
    REPEAT = 110,
    ENDWHILE = 111,

    //OPERATORS
    EQ = 201,
    PLUS = 202,
    MINUS = 203,
    ASTERISK = 204,
    SLASH = 205,
    EQEQ = 206,
    NOTEQ = 207,
    LT = 208,
    LTEQ = 209,
    GT = 210,
    GTEQ = 211,

    //INVALID
    INVALID = 400
};

const std::string BASE_TOKENS[] = {
    "NEWLINE", // 0 
    "NUMBER",
    "IDENT",
    "STRING", // 3
};

const std::string KEYWORD_TOKENS[] = {
    "LABEL",    // 101
    "GOTO",     
    "PRINT",    
    "INPUT",    
    "LET",      
    "IF",  
    "THEN",     
    "ENDIF",    
    "WHILE",    
    "REPEAT",   
    "ENDWHILE"  // 111
};

const std::string OPERATOR_TOKENS[] = {
    "EQ",       // 201
    "PLUS",     
    "MINUS",    
    "ASTERISK", 
    "SLASH",    
    "EQEQ",     
    "NOTEQ",    
    "LT",       
    "LTEQ",     
    "GT",       
    "GTEQ"      // 211
};

std::string getKindName(TokenType kind) {
    if (kind>= NEWLINE && kind <= STRING) {
        return BASE_TOKENS[kind];
    }

    if (kind >= LABEL && kind <= ENDWHILE) {
        return KEYWORD_TOKENS[kind-101];
    }

    if (kind >= EQ && kind <= GTEQ) {
        return OPERATOR_TOKENS[kind - 201];
    }

    return  "INVALID";
}

class Token {
private:
    std::string mTokenText;
    TokenType mTokenKind;

public:
    static TokenType checkIfKeyword(std::string s) {

        for (int i = LABEL; i != ENDWHILE + 1; ++i) {
            TokenType type {static_cast<TokenType>(i)};
            if (s == KEYWORD_TOKENS[type-LABEL]) {
                return type;
            }
        }
        return TokenType::IDENT;
    }

    Token(std::string tokenText, TokenType tokenKind) 
        :mTokenText{tokenText}, mTokenKind{tokenKind}
    {

    }

    //setters
    void setToken(std::string tText, TokenType tKind) {
            mTokenText = tText;
            mTokenKind = tKind;
    }

    //getters
    TokenType getKind() {
        return mTokenKind;
    }

    std::string getText() {
        return mTokenText;
    }
    Token() {}

    

};


std::ostream& operator<<(std::ostream& out, const TokenType type) {
    if (type == ENDOFFILE) {
       out << "ENDOFFILE"; 
    } else if (type >= NEWLINE && type <= STRING) {
        out << BASE_TOKENS[type - 0];
    } else if (type >= LABEL && type <= ENDWHILE) {
        out <<  KEYWORD_TOKENS[type - 101];
    } else if (type >= EQ && type <= GTEQ) {
        out << OPERATOR_TOKENS[type-201];
    } else {
        out << "UNKNOWN TYPE";
    }

    return out;
}

#endif
