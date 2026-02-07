#include <algorithm>
#include "../include/parser/parser.hpp"

std::vector<std::unique_ptr<node::Stmt>> Parser::parse() {
    std::vector<std::unique_ptr<node::Stmt>> statements;
    
    while (currentToken.type != Token::Type::LastToken) {
        auto stmt = statement();
        if (stmt) {
            stmt->lineNumber = 0;
            statements.push_back(std::move(stmt));
        }
    }
    
    // Sort program statements by line number.
    std::sort(program.begin(), program.end(), 
        [](const auto& lineAndStmt1, const auto& lineAndStmt2) { 
            return lineAndStmt1.first < lineAndStmt2.first;
        });
    
    // Add sorted program statements to the result.
    for (auto& [lineNum, stmt] : program) {
        statements.push_back(std::move(stmt));
    }

    return statements;
}

std::unique_ptr<node::Expr> Parser::comparison() {
    auto left = expression();

    if (isComparison(currentToken)) {
        CompareOp op;
        switch (currentToken.type) {
            case Token::Type::Less:
                op = CompareOp::Less;
                break;
            case Token::Type::Greater:
                op = CompareOp::Greater;
                break;
            default:
                throw std::runtime_error("Expect comparison operator");
        }

        nextToken();
        auto right = expression();
        return std::make_unique<node::CompareExpr>(std::move(left), op, std::move(right));
    }    

    return left;
}

bool Parser::isComparison(const Token& token) const {
    return token.type == Token::Type::Less ||
           token.type == Token::Type::Greater;
}

// Parses addition and subtraction expressions (lowest precedence).
std::unique_ptr<node::Expr> Parser::expression() {
    auto left = term();
    
    while (isPlus(currentToken) || isMinus(currentToken)) {
        Op op;
        switch (currentToken.type) {
            case Token::Type::Plus:
                op = Op::Plus;
                break;
            case Token::Type::Minus:
                op = Op::Minus;
                break;
            default:
                throw std::runtime_error("Expect '+' or '-'");
                break;
        }

        nextToken();
        auto right = term();
        auto result = std::make_unique<node::BinaryExpr>(std::move(left), op, std::move(right));
        left = std::move(result);
    }

    return left;
}

bool Parser::isPlus(const Token& token) const {
    return token.type == Token::Type::Plus;
}

bool Parser::isMinus(const Token& token) const {
    return token.type == Token::Type::Minus;
}

// Parses multiplication and division expressions (higher precedence).
std::unique_ptr<node::Expr> Parser::term() {
    auto left = factor();

    while (isMultiply(currentToken) || isDivide(currentToken)) {
        Op op;
        switch (currentToken.type) {
            case Token::Type::Mult:
                op = Op::Multiply;
                break;
            case Token::Type::Div:
                op = Op::Divide;
                break;
            default:
                throw std::runtime_error("Expect '*' or '/'");
                break;
        }

        nextToken();
        auto right = factor();
        left = std::make_unique<node::BinaryExpr>(std::move(left), op, std::move(right));
    }

    return left;
}

bool Parser::isMultiply(const Token& token) const {
    return token.type == Token::Type::Mult;
}

bool Parser::isDivide(const Token& token) const {
    return token.type == Token::Type::Div;
}

// Parses atomic expressions: numbers, variables, or parenthesized expressions. 
std::unique_ptr<node::Expr> Parser::factor() {
    if (currentToken.type == Token::Type::Number) {
        return parseNumber();
    } 
    else if (currentToken.type == Token::Type::Identifier) {
        return parseVariable();
    }
    else if (currentToken.type == Token::Type::LeftParenthesis) {
        return parseParenthesizedExpr();
    }

    throw std::runtime_error(
        "Invalid factor: expected number, variable or '(' but got '" + currentToken.text + "'");
}

std::unique_ptr<node::Expr> Parser::parseNumber() {
    auto value = std::stod(currentToken.text);
    nextToken();

    return std::make_unique<node::LiteralExpr>(value);
}

std::unique_ptr<node::Expr> Parser::parseVariable() {
    std::string name = currentToken.text;
    nextToken();

    return std::make_unique<node::VarExpr>(name);
}

std::unique_ptr<node::Expr> Parser::parseParenthesizedExpr() {
    eat(Token::Type::LeftParenthesis);
    auto expr = expression();
    eat(Token::Type::RightParenthesis);

    return expr; 
}

// Parses a statement.
std::unique_ptr<node::Stmt> Parser::statement() {
    if (currentToken.type == Token::Type::Number) {
        // Save the line number.
        int lineNumber = std::stoi(currentToken.text);
        nextToken();

        std::unique_ptr<node::Stmt> stmt;

        if (currentToken.type == Token::Type::Keyword) {
            if (currentToken.text == "LET") {
                nextToken();
                stmt = letStmt();
            } else if (currentToken.text == "PRINT") {
                nextToken();
                stmt = printStmt();
            } else if (currentToken.text == "IF") {
                nextToken();
                stmt = ifStmt();
            } else {
                throw std::runtime_error("Unknown keyword: " + currentToken.text);
            }
        } else {
            auto expr = expression();
            stmt = std::make_unique<node::PrintStmt>(std::move(expr));
        }

        if (stmt) {
            stmt->lineNumber = lineNumber;
            program.push_back({lineNumber, std::move(stmt)});
        }

        return nullptr;
    }
    
    auto expr = expression();
    return std::make_unique<node::PrintStmt>(std::move(expr));
}

std::unique_ptr<node::Stmt> Parser::letStmt() {
    // Expect variable name.
    if (currentToken.type != Token::Type::Identifier) {
        throw std::runtime_error("Expected identifier after LET!");
    }
    
    std::string variableName = currentToken.text;
    nextToken();
    
    eat(Token::Type::Equal);

    auto expr = expression();
    return std::make_unique<node::LetStmt>(variableName, std::move(expr));
}

std::unique_ptr<node::Stmt> Parser::printStmt() {
    auto expr = expression();
    return std::make_unique<node::PrintStmt>(std::move(expr));
}

std::unique_ptr<node::Stmt> Parser::ifStmt() {
    auto condition = comparison();

    // Expect THEN keyword.
    if (currentToken.type != Token::Type::Keyword || currentToken.text != "THEN") {
        throw std::runtime_error("Expected 'THEN' after IF condition.");
    }
    nextToken();
 
    std::unique_ptr<node::Stmt> thenStmt;

    if (currentToken.type == Token::Type::Keyword) {
        if (currentToken.text == "PRINT") {
            nextToken();
            thenStmt = printStmt();
        } else if (currentToken.text == "LET") {
            nextToken();
            thenStmt = letStmt();
        } else {
            throw std::runtime_error("Unsupported statement after THEN: " + currentToken.text);
        }
    } else {
        auto expr = expression();
        thenStmt = std::make_unique<node::PrintStmt>(std::move(expr));
    }
    
    if (!thenStmt) {
        throw std::runtime_error("Expected statement after THEN.");
    }

    return std::make_unique<node::IfStmt>(std::move(condition), std::move(thenStmt));
}

// Consumes a token of expected type, advances to next token.
void Parser::eat(Token::Type expectedType) {
    if (currentToken.type != expectedType) {
        throw std::runtime_error("Unexpected token type!");
    }

    nextToken();
}

// Advances to the next token in the stream.
void Parser::nextToken() {
    if (tokenIndex + 1 < tokensVector.size()) {
        tokenIndex++;
        currentToken = tokensVector[tokenIndex];
    } else {
        currentToken = {Token::Type::LastToken, ""};
    }
}