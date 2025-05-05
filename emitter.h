#ifndef EMITTER_H
#define EMITTER_H

#include <fstream>
#include <iostream>
#include <string>
class Emitter {
    std::ofstream mPath{};
    std::string mHeader{};
    std::string mCode{};
public:
    Emitter(std::string path)
        :mPath{path}    { 
    }

    void emit(std::string code) {
            mCode += code;
    }

    void emitLine(std::string code) {
            mCode += code + '\n';
    }

    void headerLine(std::string header) {
            mHeader += header + '\n';
    }

    void writeFile() {
        if (mPath.is_open()) {

            mPath << mHeader;
            mPath << mCode;
            mPath.close();
        } else {
            std::cerr <<"unable to open file\n";
        }
    }

};

#endif
