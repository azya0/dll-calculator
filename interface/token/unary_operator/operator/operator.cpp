#include "operator.h"

Operator::Operator(std::shared_ptr<FuncT> _math,
                   std::string _value,
                   unsigned char _priority
    ) : UnaryOperator(_math, _value)
{
    priority = _priority;
}

unsigned char Operator::getPriority() const {
    return priority;
}
