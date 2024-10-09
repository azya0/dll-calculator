#pragma once

#include "../token/token.h"
#include "../value/value.h"

#include <stack>
#include <memory>
#include <functional>
#include <stdexcept>

using StackT = std::stack<std::shared_ptr<Token>>;

class Operator : public Token {
private:
    using FuncT = std::function<double(std::vector<double>&)>;

    std::shared_ptr<FuncT> math;
    unsigned char priority;
    unsigned char valueRequire;
public:
    Operator(
        std::shared_ptr<FuncT> _math,
        unsigned char _priority,
        unsigned char _valueRequire
    );

    StatusType getStatus() const;

    unsigned char getPriority() const;

    void doMath(StackT& stack) const;

    double Test(std::vector<double>&) const;
};
