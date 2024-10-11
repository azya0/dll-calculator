#pragma once

#include "../token.h"
// without .cpp file to build .dll

class Value : public Token {
private:
    double value;
public:
    Value(double _value) : value(_value) {};

    StatusType getStatus() const {
        return StatusType::VALUE;
    };

    double getValue() const {
        return value;
    };
};
