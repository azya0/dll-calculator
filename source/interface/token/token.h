#pragma once

enum StatusType {
    EMPTY = 0,
    OPERATOR,
    VALUE,
};

class Token {
public:
    virtual StatusType getStatus() const = 0;
};
