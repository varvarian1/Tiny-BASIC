#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "logger/logging.hpp"
#include "cli/arg_parser.hpp"
#include "interpreter/interpreter.hpp"

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

    Logger logger("../log/app.log", WRITE);

    logger.log(INFO, "Program started");

    ArgumentParser argParser;
    if (!argParser.parse(argc, argv)) {
        logger.log(ERROR, "Failed to parse command line arguments");
        std::cerr << "Error: Failed to parse command line arguments" << std::endl;
        return 1;
    }
    logger.log(INFO, "Command line arguments parsed successfully");

    if (argc < 2) {
        logger.log(ERROR, "No input file specified.");
        std::cerr << "Usage: " << argv[0] << " <filename.bas>" << std::endl;
        return 1;
    }

    std::string filePath = argv[argc-1];
    logger.log(INFO, "Input file: " + filePath);

    std::string input = readFile(filePath);
    if (input.empty()) {
        logger.log(ERROR, "Empty input or file read error");
        return 1;
    }

    system("./../script.sh");

    logger.log(INFO, "Starting lexical analysis");
    Logger lexerLog("../log/lexer.log", REWRITE);
    Lexer lexer;

    try {
        // Lexer
        auto tokens = lexer.tokenize(input);
        logger.log(INFO, "Lexical analysis completed");

        lexerLog.lexerLog(tokens);
        logger.log(DEBUG, "Lexer tokens written to lexer.log");

        // Parser
        logger.log(INFO, "Starting syntax analysis");

        Parser parser(tokens);
        auto ast = parser.parse();

        logger.log(INFO, "Syntax analysis completed");

        // AST
        std::cout << "AST: " << std::endl;
        for (const auto& stmt : ast) {
            stmt->print();
            std::cout << std::endl;
        }

        logger.log(DEBUG, "AST printed to console");

        // Interpreter
        logger.log(INFO, "Starting interpretation");

        Interpreter interpreter;
        interpreter.execute(ast);

        logger.log(INFO, "Interpretation completed successfully");
    } catch (...) {
        logger.log(ERROR, "Unknown runtime error");
        return 1;
    }

    logger.log(INFO, "Program finished successfully");
    return 0;
}
