#ifndef LEXER_H
#define LEXER_H


#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include "token.h"


bool isDigit(char c);
bool isAlnum(char c);

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

    void abort(std::string message) {
        std::cerr << "Lexing error." << message << '\n';
        std::exit(1);
    }

    void skipWhitespaces() {
        while (currChar == ' ' || currChar == '\t' || currChar == '\r') {
            nextChar();
        }
    }

    void skipComment() {
        if (currChar == '#') {
            while (currChar != '\n') {
                nextChar();
            }
        }
    }

    // take a look 2 chars ahead
    char peek() {
        if ((currPos + 1) >= source.length()) {
            return '\0';
        }

        return source[currPos + 1];
    }

    //getters
    char getCurrChar() {
        return currChar;
    }

    

    Token getToken() {
        skipWhitespaces();
        skipComment();
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
            case '=':
                if (peek() == '=') {
                    char lastChar = currChar; 
                    nextChar();
                    std::string tokenText;
                    tokenText += lastChar;
                    tokenText += currChar;
                    token.setToken( tokenText, EQEQ);
                    break;
                }   
                token.setToken(std::string(1, currChar) , EQ);
                break;
            case '<':
                if (peek() == '=') {
                    char lastChar = currChar;
                    nextChar();
                    std::string tokenText;
                    tokenText += lastChar;
                    tokenText += currChar;
                    token.setToken(tokenText, LTEQ);
                    break;
                }
                token.setToken(std::string(1, currChar), LT);
                break;
            case '>':
                if (peek() == '=') {
                    char lastChar = currChar;
                    nextChar();
                    std::string tokenText;
                    tokenText += lastChar;
                    tokenText += currChar;
                    token.setToken(tokenText, GTEQ);
                    break;
                }
                token.setToken(std::string(1, currChar), GT);
                break;

             case '\"' : {
                nextChar();
                int startIdx = currPos;
                while (currChar != '\"') {
                        if (currChar == '\r' || currChar == '\n' || currChar =='\t' || currChar == '\\' || currChar == '%') {
                        abort("Invalid character in string");
                        break;
                    }
                    nextChar();
                }
                token.setToken(source.substr(startIdx, currPos-startIdx), STRING);
                break;
            }
             case '!':
                if (peek() == '=') {
                    char lastChar = currChar;
                    nextChar();
                    std::string tokenText;
                    tokenText += lastChar;
                    tokenText += currChar;
                    token.setToken(tokenText, NOTEQ);
                    break;
                } else {
                    std::string fullMsg = " '!' not followed by '=' : ";
                    fullMsg.push_back(currChar);
                    abort(fullMsg) ;
                    break;
                }


                  
          default:

             

                if (isDigit(currChar)) {
                    int startIdx = currPos;

                    while(isDigit(peek())) {
                            nextChar();
                    }
                    if (peek() == '.') {
                        nextChar();
                        if (!isDigit(peek())) {
                            abort("invalid decimal. no trailing number after decimal point");
                            break;
                        }
                        while(isDigit(peek())) {
                            nextChar();
                        }
                    }

                    token.setToken(source.substr(startIdx, currPos-startIdx + 1), NUMBER);

                    break;
                }

                if (isAlnum(currChar)) {
                    int startIdx = currPos;

                    while(isAlnum(peek())) {
                        nextChar();
                    }
                    std::string text = source.substr(startIdx, currPos- startIdx + 1);
                    TokenType type = Token::checkIfKeyword(text);
                    token.setToken(text, type);
                    break;
                }

                //unknown
                std::string fullMsg = "unknown message";
                fullMsg.push_back(currChar);
                abort(fullMsg) ;
                break;
        }

        nextChar();
        return token;
    }
};

bool isAlnum(char c) {
    c = std::tolower(c);
    return (c >= '0' && c<= '9') || ( c >='a' && c < 'z');
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

#endif
