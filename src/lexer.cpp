#include <string>

#include "lexer/lexer.hpp"

std::vector<Token> Lexer::tokenize(std::string& input) {
    std::vector<Token> tokens;

    enum State {
        InNewToken,
        InIdentifier,
        InString,
        InNumber,
        InLeftParenthesis,
        InRightParenthesis,
        InEndOfStatement,
        InComma,
        InOperator,
        InCompleteToken,
    };

    State currentState = State::InNewToken;
    std::string lexem;
    Token currentToken;
    bool decimalPoint = false;

    auto currentChar = input.begin();
    while (currentChar != input.end()) {
        switch (currentState) {
            case State::InNewToken:
                lexem.clear();
                decimalPoint = false;

                if (lut::Whitespace.at(*currentChar)) {
		            ++currentChar;
                    continue;
                }

                if (lut::RealNumeric.at(*currentChar)) {
                    lexem += *currentChar;
                    ++currentChar;
                    currentState = State::InNumber;
                }

                else if (*currentChar == '=') {
                    lexem += *currentChar;
                    ++currentChar;
                    currentToken = {Token::Type::Equal, lexem};
                    currentState = State::InCompleteToken;
                }
                else if (*currentChar == '<') {
                    lexem += *currentChar;
                    ++currentChar;
                    currentToken = {Token::Type::Less, lexem};
                    currentState = State::InCompleteToken;
                }
                else if (*currentChar == '>') {
                    lexem += *currentChar;
                    ++currentChar;
                    currentToken = {Token::Type::Greater, lexem};
                    currentState = State::InCompleteToken;
                }
                else if (*currentChar == '+') {
                    lexem += *currentChar;
                    ++currentChar;
                    currentToken = {Token::Type::Plus, lexem};
                    currentState = State::InCompleteToken;
                }
                else if (*currentChar == '-') {
                    lexem += *currentChar;
                    ++currentChar;
                    currentToken = {Token::Type::Minus, lexem};
                    currentState = State::InCompleteToken;
                }
                else if (*currentChar == '*') {
                    lexem += *currentChar;
                    ++currentChar;
                    currentToken = {Token::Type::Mult, lexem};
                    currentState = State::InCompleteToken;
                }
                else if (*currentChar == '/') {
                    lexem += *currentChar;
                    ++currentChar;
                    currentToken = {Token::Type::Div, lexem};
                    currentState = State::InCompleteToken;
                }
                else if (lut::Operator.at(*currentChar)) {
                    lexem += *currentChar;
                    ++currentChar;
                    currentState = State::InOperator;
                }
                else if (*currentChar == '(') {
                    lexem += *currentChar;
                    ++currentChar;
                    currentToken = { Token::Type::LeftParenthesis, lexem };
                    currentState = State::InCompleteToken;
                }
                else if (*currentChar == ')') {
                    lexem += *currentChar;
                    ++currentChar;
                    currentToken = { Token::Type::RightParenthesis, lexem };
                    currentState = State::InCompleteToken;
                }
                else if (*currentChar == ';') {
                    lexem += *currentChar;
                    ++currentChar;
                    currentToken = { Token::Type::Semicolon, lexem };
                    currentState = State::InCompleteToken;
                }
                else if (*currentChar == ',') {
                    lexem += *currentChar;
                    ++currentChar;
                    currentToken = { Token::Type::Comma, lexem };
                    currentState = State::InCompleteToken;
                }
                else if (*currentChar == '\"') {
                    ++currentChar;
                    currentState = State::InString;
                }
                else {
                    lexem += *currentChar;
                    ++currentChar;
                    currentState = State::InIdentifier;
                }
                break;

            case State::InIdentifier:
                if (lut::Identifier.at(*currentChar)) {
                    lexem += *currentChar;
                    ++currentChar;
                } 
                else {
                    if (keywords_map.find(lexem) != keywords_map.end()) { 
                        currentToken = { Token::Type::Keyword, lexem }; 
                    }
                    else { 
                        currentToken = { Token::Type::Identifier, lexem }; 
                    }
                    currentState = State::InCompleteToken;
                }
                break;

            case State::InString:
                if (*currentChar == '\"') {
                    ++currentChar;
                    currentToken = { Token::Type::String, lexem };
                    currentState = State::InCompleteToken;
                } else {
                    lexem += *currentChar;
                    ++currentChar;
                }
                break;

            case State::InNumber:
                if (lut::RealNumeric.at(*currentChar)) {
                    if (*currentChar == '.') {
                        if (decimalPoint) {
                            std::cerr << "{Lexer} bad numeric construction";
                        } else {
                            decimalPoint = true;
                        }
                    }
                    lexem += *currentChar;
                    ++currentChar;
                } else {
                    if (lut::Identifier.at(*currentChar)) {
                        std::cerr << "{Lexer} Invalid number" << std::endl;
                    }
                    currentToken = { Token::Type::Number, lexem };
                    currentState = State::InCompleteToken;
                }
                break;

            case State::InOperator:
                if (lut::Operator.at(*currentChar)) {
                    lexem += *currentChar;
                    ++currentChar;
                } else {
                    currentToken = { Token::Type::Operator, lexem };
                    currentState = State::InCompleteToken;
                }

                break;

            case State::InCompleteToken:
                tokens.push_back(currentToken);
                currentState = State::InNewToken;
                break;
        }
    }

    if (currentState != State::InNewToken && !lexem.empty()) {
        if (currentState == State::InIdentifier) {
            if (keywords_map.find(lexem) != keywords_map.end()) {
                currentToken = { Token::Type::Keyword, lexem };
            } else {
                currentToken = { Token::Type::Identifier, lexem };
            }
        }
        tokens.push_back(currentToken);
    }

    return tokens;
}

void Lexer::print(std::vector<Token>& tokens) {
    for (const auto& token : tokens) {
        std::cout << "Token: ";
        switch (token.type) {
            case Token::Type::Number:
                std::cout << "Number      ";
                break;
		std::cout << "New line    ";
		break;
            case Token::Type::String:
                std::cout << "String      ";
                break;
            case Token::Type::LeftParenthesis:
                std::cout << "LeftParenthesis";
                break;
            case Token::Type::RightParenthesis:
                std::cout << "RightParenthesis";
                break;
            case Token::Type::Semicolon:
                std::cout << "Semicolon    ";
                break;
            case Token::Type::Comma:
                std::cout << "Comma        ";
                break;
            case Token::Type::Plus:
                std::cout << "Plus        ";
                break;
            case Token::Type::Minus:
                std::cout << "Minus       ";
                break;
            case Token::Type::Mult:
                std::cout << "Mult        ";
                break;
            case Token::Type::Div:
                std::cout << "Div         ";
                break;
            case Token::Type::Equal:
                std::cout << "Equal       ";
                break;
            case Token::Type::Less:
                std::cout << "Less        ";
                break;
            case Token::Type::Greater:
                std::cout << "Greater     ";
                break;
            case Token::Type::Operator:
                std::cout << "Operator    ";
                break;
            case Token::Type::Identifier:
                std::cout << "Identifier  ";
                break;
            case Token::Type::Keyword:
                std::cout << "Keyword     ";
                break;
            case Token::Type::Unknown:
                std::cout << "Unknown     ";
                break;
        }
        std::cout << "\t -> '" << token.text << "'";
        std::cout << std::endl;
    }
}
