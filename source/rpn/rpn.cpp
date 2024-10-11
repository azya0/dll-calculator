#include "rpn.h"

bool isDigit(char const & letter) {
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

template <typename T>
std::shared_ptr<T> find(MapT<T> const & map, std::string const & value) {
    auto iterator = map.find(value);

    if (iterator == map.end()) {
        throw std::runtime_error("unknown operator \"" + value + "\"");
    }

    return iterator->second;
}

void RPN::emptyBrackets(std::stack<OperT>& stack, QueueT& queue) const {
    bool wasBracket = false;
    int counter = 0;

    while (!stack.empty()) {
        auto oper = stack.top().second;

        if (oper->getValue() == "(") {
            wasBracket = true;
        } else {
            queue.push(oper);
            counter++;
        }

        stack.pop();

        if (wasBracket) {
            break;
        }
    }

    if (!wasBracket) {
        throw std::runtime_error("missing \"(\"");
    }

    if (counter == 0) {
        throw std::runtime_error("empty brackets");
    }
}

std::shared_ptr<Value> RPN::parseNumber(int& index) const {
    double value = 0;
    auto letter = std::make_shared<char>();

    for (; index < expression.size(); index++) {
        *letter = expression[index];
        if (isDigit(*letter)) {
            value = value * 10 + static_cast<double>((*letter) - '0');
        } else {
            break;
        }
    }

    if (!(letter != nullptr && (*letter) == '.')) {
        return std::make_shared<Value>(value);
    }

    index++;
    bool wasDigit = false;

    for (int counter = -1; index < expression.size(); index++, counter--) {
        *letter = expression[index];
        if (isDigit(*letter)) {
            value += static_cast<double>((*letter) - '0') * power(10, counter);

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

std::shared_ptr<RPN::OperT> RPN::parseOperator(int& index, bool wasDigit) const {
    std::string value;
    auto letter = std::make_shared<char>();

    for (; index < expression.size(); index++) {
        *letter = expression[index]; 

        if (!isDigit(*letter) && (*letter) != ' ') {
            value.push_back(*letter);
        } else {
            break;
        }
    }

    std::shared_ptr<UnaryOperator> result;

    if (!wasDigit) {
        result = find<UnaryOperator>(*operators.second, value);
    } else {
        result = find<Operator>(*operators.first, value);
    }

    return std::make_shared<OperT>(OperT({!wasDigit, result}));    
}

std::shared_ptr<RPN::QueueT> RPN::buildExpression() const {
    std::stack<OperT> stack;
    auto result = std::make_shared<QueueT>();
    bool wasDigit = false;

    for (int index = 0; index < expression.size();) {
        if (isDigit(expression[index])) {
            result->push(parseNumber(index));
            wasDigit = true;
            continue;
        } else if (expression[index] == ' ') {
            index++;
            continue;
        }

        if (expression[index] == '(') {
            stack.push({true, std::make_shared<UnaryOperator>(nullptr, "(")});
            index++;
        } else if (expression[index] == ')') {
            emptyBrackets(stack, *result);
            index++;
        } else {
            auto &[isUnar, oper] = *parseOperator(index, wasDigit);

            if (stack.empty()) {
                stack.push({isUnar, oper});
                continue;
            }

            while (!stack.empty()) {
                auto &[isPrevUnar, previous] = stack.top();

                if (isUnar) {
                    if (isPrevUnar && (previous->getValue() == "(")) {
                        break;
                    }
                } else if (isPrevUnar) {
                    break;
                } else {
                    unsigned char prevPriority = std::static_pointer_cast<Operator>(previous)->getPriority();
                    unsigned char operPriority = std::static_pointer_cast<Operator>(oper)->getPriority();

                    if (prevPriority < operPriority) {
                        break;
                    }
                }

                result->push(previous);
                stack.pop();
            }

            stack.push({isUnar, oper});
        }

        wasDigit = false;
    }

    while (!stack.empty()) {
        result->push(stack.top().second);
        stack.pop();
    }

    return result;
}

double RPN::solveExpression(QueueT &queue) const {
    auto stack = std::make_shared<StackT>();

    while (!queue.empty()) {
        auto value = std::dynamic_pointer_cast<Value>(queue.front());

        if (value != nullptr) {
            stack->push(value);
            queue.pop();
            continue;
        }

        auto oper = std::dynamic_pointer_cast<UnaryOperator>(queue.front());

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

RPN::RPN(PairT& _operators) noexcept : operators(_operators) {}

double RPN::solve(std::string _expression) {
    expression = _expression;

    return solveExpression(*buildExpression());
}
