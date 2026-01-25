#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "logger/logging.hpp"
#include "cli/arg_parser.hpp"

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

    ArgumentParser argParser;
    if (!argParser.parse(argc, argv)) {
        std::cerr << "Error: Failed to parse command line arguments." << std::endl;
        return 1;
    }

    std::string filePath = argv[argc-1];
    std::string input = readFile(filePath);

    system("./../script.sh");
    Logger logger("../log/app.log", WRITE);

    logger.log(INFO, "Program start.");

    Logger lexerLog("../log/lexer.log", REWRITE);
    Lexer lexer;
    auto tokens = lexer.tokenize(input);
    
    lexerLog.lexerLog(tokens);
    lexer.print(tokens);

    std::cout << std::endl;
    std::cout << "Parser: " << std::endl;
    
    Parser parser(tokens);
    auto ast = parser.parse();

    std::cout << "AST: " << std::endl;
    for (const auto& stmt : ast) {
        stmt->print();
	    std::cout << std::endl;
    } 

    return 0;
}
