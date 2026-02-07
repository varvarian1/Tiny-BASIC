#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <unordered_map>

// Arithmetic operations.
enum class Op {
    Plus,       // +
    Minus,      // -
    Multiply,   // *
    Divide      // /
};

enum class CompareOp {
    Less,       // <
    Greater     // >
};

namespace node {
    class EvaluationContext {
    public:
        double getVariable(const std::string& name) const {
            auto it = variables.find(name);
            if (it == variables.end()) {
                throw std::runtime_error("Undefined variable: " + name);
            }
            return it->second;
        }

        void setVariable(const std::string& name, double value) {
            variables[name] = value;
        }

        bool hasVariable(const std::string& name) const {
            return variables.find(name) != variables.end();
        }
        
        void clear() {
            variables.clear();
        }
        
        void dump() const {
            std::cout << "=== Variables ===" << std::endl;
            for (const auto& [name, value] : variables) {
                std::cout << name << " = " << value << std::endl;
            }
            std::cout << "================" << std::endl;
        }

    private:
        std::unordered_map<std::string, double> variables;

    };

    // Base class for expressions.
    struct Expr {
        virtual ~Expr() = default;
        virtual void print(int indent = 0) const = 0;
        virtual double evaluate(EvaluationContext& context) const = 0;
    };

    struct LiteralExpr : Expr {
        double value;
        LiteralExpr(double v) : value(v) {}

        void print(int indent = 0) const override {
            std::cout << std::string(indent, ' ') << "Literal: " << value << std::endl; 
        }

        double evaluate(EvaluationContext& context) const override {
            return value;
        }
    };

    struct VarExpr : Expr {
        std::string name;
        VarExpr(std::string n) : name(std::move(n)) {}
        
        void print(int indent = 0) const override {
            std::cout << std::string(indent, ' ') << "Variable: " << name << std::endl;
        }

        double evaluate(EvaluationContext& context) const override {
            return context.getVariable(name);
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

        double evaluate(EvaluationContext& context) const override {
            double leftVal = left->evaluate(context);
            double rightVal = right->evaluate(context);
            
            switch (op) {
                case Op::Plus:
                    return leftVal + rightVal;
                case Op::Minus:
                    return leftVal - rightVal;
                case Op::Multiply:
                    return leftVal * rightVal;
                case Op::Divide:
                    if (rightVal == 0) {
                        throw std::runtime_error("Division by zero");
                    }
                    return leftVal / rightVal;
                default:
                    throw std::runtime_error("Unknown operator");
            }
        }
    };

    struct CompareExpr : Expr {
        std::unique_ptr<Expr> left, right;
        CompareOp op;
        CompareExpr(std::unique_ptr<Expr> l, CompareOp op, std::unique_ptr<Expr> r)
            : left(std::move(l)), right(std::move(r)), op(op) {}

        void print(int indent = 0) const override {
            std::cout << std::string(indent, ' ') << "CompareExpr: ";
            switch (op) {
                case CompareOp::Less:
                    std::cout << "<";
                    break;
                case CompareOp::Greater:
                    std::cout << ">";
                    break;
            }

            std::cout << std::endl;
            left->print(indent + 2);
            right->print(indent + 2);
        }

        double evaluate(EvaluationContext& context) const override {
            double leftValue = left->evaluate(context);
            double rightValue = right->evaluate(context);

            switch (op) {
                case CompareOp::Less:
                    return (leftValue < rightValue) ? 1.0 : 0.0;
                case CompareOp::Greater:
                    return (leftValue > rightValue) ? 1.0 : 0.0;
                default:
                    throw std::runtime_error("Unknown comparison operator.");
            }
        }
    };

    // Base class for statements.
    struct Stmt {
        int lineNumber = 0;

        virtual ~Stmt() = default;
        virtual void print(int indent = 0) const = 0;
        virtual void execute(EvaluationContext& context) const = 0;
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

        void execute(EvaluationContext& context) const override {
            double val = value->evaluate(context);
            context.setVariable(variableName, val);
        }
    };

    struct PrintStmt : Stmt {
        std::unique_ptr<Expr> expr;
        PrintStmt(std::unique_ptr<Expr> e) : expr(std::move(e)) {}

        void print(int indent = 0) const override {
            std::cout << std::string(indent, ' ') << "PrintStmt: " << std::endl;
            if (expr) expr->print(indent + 2);
        }

        void execute(EvaluationContext& context) const override {
            double val = expr->evaluate(context);
            
            if (val == static_cast<int>(val)) {
                std::cout << static_cast<int>(val);
            }
            else {
                std::cout << val;
            }

            std::cout << std::endl;
        }
    };

    struct IfStmt : Stmt {
        std::unique_ptr<Expr> condition;
        std::unique_ptr<Stmt> thenStmt;

        IfStmt(std::unique_ptr<Expr> cond, std::unique_ptr<Stmt> thenStmt)
            : condition(std::move(cond)), thenStmt(std::move(thenStmt)) {}

        void print(int indent = 0) const override {
            std::cout << std::string(indent, ' ') << "IfStmt:" << std::endl;
            if (condition) {
                std::cout << std::string(indent + 2, ' ') << "Condition:" << std::endl;
                condition->print(indent + 4);
            }
            if (thenStmt) {
                std::cout << std::string(indent + 2, ' ') << "Then:" << std::endl;
                thenStmt->print(indent + 4);
            }
        }

        void execute(EvaluationContext& context) const override {
            double conditionValue = condition->evaluate(context);
            
            // 0 is false, anything else is true.
            if (conditionValue != 0.0) {
                thenStmt->execute(context);
            }
        }
    };
};
