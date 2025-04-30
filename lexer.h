#include <iostream>
#include <string>

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


};
