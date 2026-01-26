#include <iostream>
#include <getopt.h>
#include <fstream>

#include "cli/arg_parser.hpp"

bool ArgumentParser::parse(int argc, char **argv) {
    int opt;

    while ((opt = getopt(argc, argv, "ht")) != -1) {
        switch (opt) {
            case 'h':
                help();
                break;
            case 't':
                readLog("../log/lexer.log");
                break;
            default:
                std::cerr << "Unknown argument. Use -h for help.\n";
                break;
        }
    }

    for (int i = optind; i < argc; i++) {
        args.push_back(argv[i]);
    }

    if (args.size() > 0) {
        return true;
    }

    return false;
}

void ArgumentParser::help() {
    std::cout << "Usage: basic [OPTION]... [FILE]\n"
              << "A compiler for the Tiny BASIC programming language.\n\n"
              << "Options:\n"
              << "  -h, --help          display this help and exit\n"
              << "  -t, --tokens        display tokens\n"
              << "  -a, --ast           display abstract syntax tree\n\n";
}

// Reads and displays the contents of a log file to the console.
void ArgumentParser::readLog(std::string filename) {
    std::string line;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: can't open '" << filename << "' file." << std::endl;
    }

    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}
