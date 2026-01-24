#include <iostream>
#include <getopt.h>

#include "cli/arg_parser.hpp"

bool ArgumentParser::parse(int argc, char **argv) {
    int opt;

    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch (opt) {
            case 'h':
                help();
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
