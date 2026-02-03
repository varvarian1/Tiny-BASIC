#pragma once

#include <vector>
#include <memory>

#include "parser/node.hpp"

class Interpreter {
public:
    Interpreter() = default;

    void execute(const std::vector<std::unique_ptr<node::Stmt>>& program);
    const node::EvaluationContext& getContext() const { return context; }
    void dumpVariables() const { context.dump(); }

private:
    node::EvaluationContext context;

};