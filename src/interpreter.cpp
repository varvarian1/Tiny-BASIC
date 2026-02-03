#include <iostream>

#include "interpreter/interpreter.hpp"

void Interpreter::execute(const std::vector<std::unique_ptr<node::Stmt>>& program) {
    context.clear();
    
    std::cout << "Execute: " << std::endl;

    for (const auto& stmt : program) {
        try {
            stmt->execute(context);
        } catch (const std::exception& e) {
            std::cerr << "Runtime error at line " << stmt->lineNumber 
                     << ": " << e.what() << std::endl;
            break;
        }
    }
    
    std::cout << "End of program." << std::endl;
}
