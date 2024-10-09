#include "operator.h"

Operator::Operator(std::shared_ptr<FuncT> _math, unsigned char _priority, unsigned char _valueRequire) {
    math = std::make_shared<FuncT>(*_math);

    priority = _priority;
    valueRequire = _valueRequire;
}

StatusType Operator::getStatus() const {
    return StatusType::OPERATOR;
}

unsigned char Operator::getPriority() const {
    return priority;
}

void Operator::doMath(StackT &stack) const {
    if (stack.size() < valueRequire) {
        throw std::runtime_error("Additional opetator has lower than 2 value");
    }

    std::vector<double> values;

    for (unsigned char _ = 0; _ < valueRequire; _++) {
        auto valuePtr = std::static_pointer_cast<Value>(stack.top());

        values.push_back(valuePtr->getValue());
        stack.pop();
    }

    stack.push(std::make_shared<Value>((*math)(values)));
}

double Operator::Test(std::vector<double>& testing) const {
    return (*math)(testing);
}
