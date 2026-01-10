#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "lexer/lexer.hpp"

static std::string readFile(const std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
    }

    std::ostringstream sstr;
    sstr << file.rdbuf();
    return sstr.str();
}

int main(int argc, char *argv[]) {

    std::string filePath = argv[argc-1];
    std::string input = readFile(filePath);

    Lexer lexer;
    auto tokens = lexer.tokenize(input);
    lexer.print(tokens);

    return 0;
}
