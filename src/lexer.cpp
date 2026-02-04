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

                if (isWhitespace(*currentChar)) {
		            ++currentChar;
                    continue;
                }

                if (isDigit(*currentChar)) {
                    lexem += *currentChar;
                    ++currentChar;
                    currentState = State::InNumber;
                    break;
                }

                if (isIdentifierStart(*currentChar)) {
                    lexem += *currentChar;
                    ++currentChar;
                    currentState = State::InIdentifier;
                    break;
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
                while (currentChar != input.end() && isIdentifierChar(*currentChar)) {
                    lexem += *currentChar;
                    ++currentChar;
                }

                currentToken = keywordOrIdentifier(lexem);
                currentState = State::InCompleteToken;
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
                while (currentChar != input.end() && isRealNumeric(*currentChar)) {
                    if (*currentChar == '.') {
                        if (decimalPoint) {
                            std::cerr << "{Lexer} bad numeric construction";
                        }
                        else {
                            decimalPoint = true;
                        }
                    }

                    lexem += *currentChar;
                    ++currentChar;
                }

                if (currentChar != input.end() && isIdentifierStart(*currentChar)) {
                    std::cerr << "{Lexer} Invalid number: " << lexem << *currentChar << std::endl;

                    currentToken = { Token::Type::Number, lexem };
                    currentState = State::InCompleteToken;
                    break;
                }

                currentToken = { Token::Type::Number, lexem };
                currentState = State::InCompleteToken;
                break;

            case State::InCompleteToken:
                tokens.push_back(currentToken);
                currentState = State::InNewToken;
                break;
        }
    }

    if (currentState == State::InIdentifier && !lexem.empty()) {
        tokens.push_back(keywordOrIdentifier(lexem));
    }
    else if (currentState == State::InNumber && !lexem.empty()) {
        tokens.emplace_back(Token::Type::Number, lexem);
    }
    else if (currentState == State::InCompleteToken) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

Token Lexer::keywordOrIdentifier(const std::string& lexem) {
    if (lexem.empty())
        return { Token::Type::Identifier, lexem };

    switch (lexem[0]) {
        case 'L':
            if (lexem == "LET")
                return { Token::Type::Keyword, lexem };
            break;
            
        case 'P':
            if (lexem == "PRINT")
                return { Token::Type::Keyword, lexem };
            break;

        case 'G':
            if (lexem == "GOTO")
                return { Token::Type::Keyword, lexem };
            else if (lexem == "GOSUB")
                return { Token::Type::Keyword, lexem };
            break;

        case 'I':
            if (lexem == "IF")
                return { Token::Type::Keyword, lexem };
            else if (lexem == "INPUT")
                return { Token::Type::Keyword, lexem };
            break;

        case 'T':
            if (lexem == "THEN")
                return { Token::Type::Keyword, lexem };
            break;

        case 'R':
            if (lexem == "RETURN")
                return { Token::Type::Keyword, lexem };
            break;

        case 'E':
            if (lexem == "END")
                return { Token::Type::Keyword, lexem };
            break;
                  
    }

    return { Token::Type::Identifier, lexem };
}
