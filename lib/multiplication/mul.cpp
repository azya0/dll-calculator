#include "../dllScheme.h"

Data LIBRARY_EXPORT getData() noexcept {
    return {"*", 1, false};
}

void doMath(StackT& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Multiplicational operator require 2 values");
    }

    double result = 1;

    for (unsigned char _ = 0; _ < 2; _++) {
        result *= stack.top()->getValue();

        stack.pop();
    }

    stack.push(std::make_shared<Value>(result));
}
