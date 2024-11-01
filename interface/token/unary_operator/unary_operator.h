#pragma once

#include "../token.h"
#include "../value/value.h"

#include <stack>
#include <memory>
#include <functional>
#include <stdexcept>

using StackT = std::stack<std::shared_ptr<Value>>;
using FuncT = std::function<void(StackT&)>;

class UnaryOperator : public Token {
protected:
    std::shared_ptr<FuncT> math;
    std::string value;
public:
    UnaryOperator(std::shared_ptr<FuncT> math, std::string value);

    StatusType getStatus() const;

    std::string const & getValue() const;

    void doMath(StackT& stack) const;
};
