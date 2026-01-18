#pragma once

#include <memory>
#include <string>
#include <iostream>

// Arithmetic operations.
enum class Op {
    Plus,       // +
    Minus,      // -
    Multiply,   // *
    Divide      // /
};

namespace node {
    // Base class for expressions.
    struct Expr {
        virtual ~Expr() = default;
        virtual void print(int indent = 0) const = 0;
    };

    struct LiteralExpr : Expr {
        double value;
        LiteralExpr(double v) : value(v) {}

        void print(int indent = 0) const override {
            std::cout << std::string(indent, ' ') << "Literal: " << value << std::endl; 
        }
    };

    struct VarExpr : Expr {
        std::string name;
        VarExpr(std::string n) : name(std::move(n)) {}
        
        void print(int indent = 0) const override {
            std::cout << std::string(indent, ' ') << "Variable: " << name << std::endl;
        }
    };

    struct BinaryExpr : Expr {
        std::unique_ptr<Expr> left, right;
        Op op;
        BinaryExpr(std::unique_ptr<Expr> l, Op o, std::unique_ptr<Expr> r)
            : left(std::move(l)), right(std::move(r)), op(o) {}

        void print(int indent = 0) const override {
            std::cout << std::string(indent, ' ') << "BinaryExpr: ";
            switch (op) {
                case Op::Plus:
                    std::cout << "+";
                    break;
                case Op::Minus:
                    std::cout << "-";
                    break;
                case Op::Multiply:
                    std::cout << "*";
                    break;
                case Op::Divide:
                    std::cout << "/";
                    break;
            }
            std::cout << std::endl;
            left->print(indent + 2);
            right->print(indent + 2);
        }
    };

    // Base class for statements.
    struct Stmt {
        int lineNumber;

        virtual ~Stmt() = default;
        virtual void print(int indent = 0) const = 0;
    };

    struct LetStmt : Stmt {
        std::string variableName;
        std::unique_ptr<Expr> value;
        LetStmt(std::string name, std::unique_ptr<Expr> val)
            : variableName(std::move(name)), value(std::move(val)) {}

        void print(int indent = 0) const override {
            std::cout << std::string(indent, ' ') << "LetStmt: " << variableName << "=" << std::endl;
            if (value) value->print(indent + 2);
        }
    };

    struct PrintStmt : Stmt {
        std::unique_ptr<Expr> expr;
        PrintStmt(std::unique_ptr<Expr> e) : expr(std::move(e)) {}

        void print(int indent = 0) const override {
            std::cout << std::string(indent, ' ') << "PrintStmt: " << std::endl;
            if (expr) expr->print(indent + 2);
        }
    };
};
