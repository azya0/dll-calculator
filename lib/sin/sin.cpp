#include "../dllScheme.h"

#include <cmath>

Data LIBRARY_EXPORT getData() noexcept {
    return {"sin", 255, true};
}

void doMath(std::stack<std::shared_ptr<Value>>& stack) {
    if (stack.size() < 1) {
        throw std::runtime_error("Unar subtractional operator require 1 value");
    }

    double result = sin(stack.top()->getValue());

    stack.pop();

    stack.push(std::make_shared<Value>(result));
}
