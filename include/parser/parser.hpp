#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>

#include "lexer/lexer.hpp"
#include "parser/node.hpp"

/**
 * Parser.
 * Converts tokens into an Abstract Syntax Tree (AST).
 */
class Parser {
public:
    
    /**
     * Constructs a parser for the given tokens.
     * tokenRef - reference to a vector of tokens produced by the lexer.
     */
    Parser(std::vector<Token>& tokensRef) : tokensVector(tokensRef), tokenIndex(0) {
        if (!tokensVector.empty()) {
	        currentToken = tokensVector[tokenIndex];
	    }
    }
    
    /**
     * Parses all tokens into a sequence of statements.
     * Return vector of AST statements in execution order.
     */
    std::vector<std::unique_ptr<node::Stmt>> parse();
    
    // Expression parsing methods.
    std::unique_ptr<node::Expr> comparison();
    std::unique_ptr<node::Expr> expression(); // Addition and subtraction.
    std::unique_ptr<node::Expr> term();	      // Multiplication and division.
    std::unique_ptr<node::Expr> factor();     // Atomic expressions.
    
    // Helper methods for factor parsing.
    std::unique_ptr<node::Expr> parseNumber();
    std::unique_ptr<node::Expr> parseVariable();
    std::unique_ptr<node::Expr> parseParenthesizedExpr();
   
    // Token type checking helpers. 
    bool isPlus(const Token& token) const;
    bool isMinus(const Token& token) const;
    bool isMultiply(const Token& token) const;
    bool isDivide(const Token& token) const;
    bool isComparison(const Token& token) const;

    // Statment parsing methods.
    std::unique_ptr<node::Stmt> statement(); // General statement.
    std::unique_ptr<node::Stmt> letStmt();   // LET statement.
    std::unique_ptr<node::Stmt> printStmt(); // PRINT statement.
    std::unique_ptr<node::Stmt> ifStmt();    // IF statement.
    
    // Token manipulation.
    void eat(Token::Type expectedType); // Consume expected token.
    void nextToken(); 			        // Advance to next token.
    
private:
    // Referance to the token vector (externally owned).
    std::vector<Token>& tokensVector;

    // Current parsing position.
    size_t tokenIndex = 0;
    Token currentToken;
    
    // Stores numbered program statements for sorting by line number.
    std::vector<std::pair<int, std::unique_ptr<node::Stmt>>> program;
};
