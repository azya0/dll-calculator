#include "../dllScheme.h"

Data LIBRARY_EXPORT getData() noexcept {
    return {"!", 255, true};
}

void doMath(std::stack<std::shared_ptr<Value>>& stack) {
    if (stack.size() < 1) {
        throw std::runtime_error("Factorial operator require 1 value");
    }

    double result = 1;
    
    double value = stack.top()->getValue();

    if (static_cast<long long int>(value) != value) {
        throw std::runtime_error("Factorial operator require long long int casting value");
    }

    for (long long int index = value; index > 1; index--) {
        result *= index;
    }

    stack.pop();

    stack.push(std::make_shared<Value>(result));
}
