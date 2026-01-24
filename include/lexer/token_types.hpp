#pragma once

#include <string>

struct Token {
    enum class Type {
        Unknown,
        Number,
        String,
        LeftParenthesis,    // (
        RightParenthesis,   // )
        Semicolon,          // ;
        Comma,              // ,
        Plus,               // +
        Minus,              // -
        Mult,               // *
        Div,                // /
        Equal,              // =
        Less,               // <
        Greater,            // >
        Operator,           // =, <, >, etc
        Identifier,         
        Keyword,
        LastToken           // EOF
    };

    Type            type = Type::Unknown;
    std::string     text = "";
};
