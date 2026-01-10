#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

#include "lexer/keywords.hpp"
#include "lexer/lookup.hpp"
#include "lexer/token_types.hpp"

struct Keyword { uint8_t placeholder_for_now = 0; };

class Lexer {
public:

    Lexer() {
        for (const auto& kw : keywords) {
            keywords_map[kw] = Keyword{};
        }
    }

    std::vector<Token> tokenize(std::string& input);
    void print(std::vector<Token>& tokens);

private:
    std::unordered_map<std::string, Keyword> keywords_map;

};
