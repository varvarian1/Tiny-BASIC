#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

#include "lexer/token_types.hpp"

class Lexer {
public:

    Lexer() = default;

    std::vector<Token> tokenize(std::string& input);

    bool isDigit(char ch) {
        return (unsigned char)(ch - '0') <= 9;
    }

    bool isRealNumeric(char ch) {
        return isDigit(ch) || ch == '.';
    }

    bool isIdentifierStart(char ch) {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
    }
    
    bool isIdentifierChar(char ch) {
        return isIdentifierStart(ch) || isDigit(ch);
    }

    bool isWhitespace(char ch) {
        return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v' || ch == '\f';
    }

    Token keywordOrIdentifier(const std::string& lexem);

};
