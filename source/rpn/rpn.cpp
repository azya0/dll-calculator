#include "rpn.h"

bool RPN::isDigit(int index) {
    char letter = expression[index];

    return letter >= '0' && letter <= '9';
}

double power(double value, int power) {
    if (value == 0) {
        return 0;
    }
    
    double result = 1;

    bool negative = power < 0;

    for (int _ = 0; _ < abs(power); _++) {
        if (negative) {
            result /= value;
        } else {
            result *= value;
        }
    }

    return result;
}

std::shared_ptr<Value> RPN::parseNumber(int& index) {
    double value = 0;
    bool isLetter = false;

    for (; index < expression.size(); index++) {
        if (isDigit(index)) {
            value = value * 10 + static_cast<double>(expression[index] - '0');
        } else {
            isLetter = true;
            break;
        }
    }

    if (!(isLetter && expression[index] == '.')) {
        return std::make_shared<Value>(value);
    }

    index++;
    bool wasDigit = false;

    for (int counter = -1; index < expression.size(); index++, counter--) {
        if (isDigit(index)) {
            value += static_cast<double>(expression[index] - '0') * power(10, counter);

            if (!wasDigit) {
                wasDigit = true;
            }
        } else {
            break;
        }
    }

    if (!wasDigit) {
        throw std::runtime_error("wrong value syntax: missing value after .");
    }

    return std::make_shared<Value>(value);
}

std::shared_ptr<Operator> RPN::parseOperator(int& index) {
    std::string value;
    char letter;

    for (; index < expression.size(); index++) {
        if (!isDigit(index) && (letter = expression[index]) != ' ') {
            value.push_back(letter);
        } else {
            break;
        }
    } 

    auto iterator = operators->find(value);
    if (iterator == operators->end()) {
        throw std::runtime_error("unknown operator \"" + value + "\"");
    }

    return iterator->second;
}

std::shared_ptr<RPN::QueueT> RPN::buildExpression() {
    auto result = std::make_shared<QueueT>();
    std::stack<std::shared_ptr<Operator>> stack;

    for (int index = 0; index < expression.size();) {
        if (isDigit(index)) {
            auto value = parseNumber(index);
            result->push(value);
        } else if (expression[index] == ' ') {
            index++;
            continue;
        } else {
            auto oper = parseOperator(index);

            if (stack.empty()) {
                stack.push(oper);
                continue;
            }

            while (!stack.empty()) {
                auto& previous = stack.top();

                if (previous->getPriority() < oper->getPriority()) {
                    break;
                }

                result->push(previous);
                stack.pop();
            }

            stack.push(oper);
        }
    }

    while (!stack.empty()) {
        result->push(stack.top());
        stack.pop();
    }

    return result;
}

double RPN::solveExpression(QueueT &queue) {
    auto stack = std::make_shared<StackT>();

    while (!queue.empty()) {
        auto value = std::dynamic_pointer_cast<Value>(queue.front());

        if (value != nullptr) {
            stack->push(value);
            queue.pop();
            continue;
        }
            
        auto oper = std::dynamic_pointer_cast<Operator>(queue.front());

        if (oper == nullptr) {
            throw std::runtime_error("unexpected error");
        }
        
        oper->doMath(*stack);
        queue.pop();
    }

    if (stack->size() != 1) {
        throw std::runtime_error("wrong expression");
    }

    return std::static_pointer_cast<Value>(stack->top())->getValue();
}

RPN::RPN(std::shared_ptr<MapT const> _operators) noexcept {
    operators = std::make_shared<MapT const>(*_operators);
}

double RPN::solve(std::string expression) {
    this->expression = expression;

    return solveExpression(*buildExpression());
}
