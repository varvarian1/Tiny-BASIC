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

    Token() = default;
    Token(Type type, const std::string& text) : type(type), text(text) {}
    Token(Type type, std::string&& text) : type(type), text(std::move(text)) {}
};
