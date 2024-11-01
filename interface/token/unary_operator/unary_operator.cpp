#include "unary_operator.h"

UnaryOperator::UnaryOperator(std::shared_ptr<FuncT> _math, std::string _value) {
    value = _value;

    if (_math != nullptr) {
        math = std::make_shared<FuncT>(*_math);
    }
}

StatusType UnaryOperator::getStatus() const {
    return StatusType::OPERATOR;
}

std::string const & UnaryOperator::getValue() const {
    return value;
}

void UnaryOperator::doMath(std::stack<std::shared_ptr<Value>>& stack) const {
    (*math)(stack);
}
