#include "../dllScheme.h"

#include <cmath>

Data LIBRARY_EXPORT getData() noexcept {
    return {"^", 2, false};
}

void doMath(StackT& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Power operator require 2 values");
    }

    double base, power;

    for (unsigned char index = 0; index < 2; index++) {
        double value = stack.top()->getValue(); 
        
        if (index == 0) {
            power = value;
        } else {
            base = value;
        }

        stack.pop();
    }

    stack.push(std::make_shared<Value>(pow(base, power)));
}
