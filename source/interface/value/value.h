#pragma once

#include "../token/token.h"

class Value : public Token {
private:
    double value;
public:
    Value(double);

    StatusType getStatus() const;

    double getValue() const;
};