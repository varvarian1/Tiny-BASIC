#pragma once

#include <vector>
#include <string>

class ArgumentParser {
public:
    ArgumentParser() = default;

    std::vector<std::string> args;

    bool parse(int argc, char **argv);
    void help();
    void readLog(std::string filename);

};
