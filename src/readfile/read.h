#ifndef READFILE
#define READFILE

#include <string>
#include <fstream>
#include <streambuf>

std::string read(std::string path) {
    std::ifstream t(path);
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    return str;
}

#endif
