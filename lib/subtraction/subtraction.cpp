#include "../dllScheme.h"

Data LIBRARY_EXPORT getData() noexcept {
    return {"-", 0, false};
}

void doMath(StackT& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Subtractional operator require 2 values");
    }

    double result = 0;

    for (unsigned char index = 0; index < 2; index++) {
        double value = stack.top()->getValue();
        
        if (index == 0) {
            result -= value;
        } else {
            result += value;
        }

        stack.pop();
    }

    stack.push(std::make_shared<Value>(result));
}
