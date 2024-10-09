#include "value.h"

Value::Value(double _value) {
    value = _value;
}

StatusType Value::getStatus() const {
    return StatusType::VALUE;
}

double Value::getValue() const {
    return value;
}
