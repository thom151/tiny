#include <iostream>
#include <string>
#include "token.h"


class Lexer {

private:
    std::string source;
    char currChar;
    int currPos;
public:
    Lexer(std::string source) 
       :source{source +'\n'}, currPos{-1}
    {

        std::cout << "SOURCE: " << source << '\n';
        if(!source.empty()) {
            currChar = source[0];
        }
        nextChar();
    }


    //This is a helper function that sets current char and current position
    void nextChar() {
        currPos += 1;
        if (currPos >= source.length()) {
            currChar = '\0';
            return;
        }
        currChar = source[currPos];
    }

    // take a look 2 chars ahead
    char peek() {
        if ((currPos + 1) > source.length()) {
            return '\0';
        }

        return source[currPos + 1];
    }

    //getters
    char getCurrChar() {
        return currChar;
    }

    

    Token getToken() {
        Token token{};
        switch (currChar) {
            case '+':
                token.setToken(std::string(1,currChar), PLUS);
                break;
            case '-':
                token.setToken(std::string(1, currChar), MINUS);
                break;
            case '*':
                token.setToken(std::string(1, currChar), ASTERISK);
                break;
            case '/':
                token.setToken(std::string(1, currChar), SLASH);
                break;
            case '\n':
                token.setToken(std::string(1, currChar), NEWLINE);
                break;
            case '\0':
                token.setToken(std::string(1, currChar), ENDOFFILE);
                break;
            default:
                //unknown
                break;  
        }

        nextChar();
        return token;
    }
};
