#pragma once

#include "../unary_operator.h"

class Operator : public UnaryOperator  {
protected:
    unsigned char priority;
public:
    Operator(
        std::shared_ptr<FuncT> math,
        std::string value,
        unsigned char priority
    );

    unsigned char getPriority() const;
};
