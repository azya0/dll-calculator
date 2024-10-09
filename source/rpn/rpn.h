#include <string>
#include <memory>
#include <queue>
#include <unordered_map>

// Удалить
#include <iostream>

#include "../interface/interfaces.h"

class RPN {
private:
    using QueueT = std::queue<std::shared_ptr<Token>>;
    using MapT = std::unordered_map<std::string, std::shared_ptr<Operator>>;

    std::shared_ptr<MapT const> operators;
    std::string expression;

    bool isDigit(int index);

    std::shared_ptr<Value> parseNumber(int& index);

    std::shared_ptr<Operator> parseOperator(int& index);

    std::shared_ptr<QueueT> buildExpression();

    double solveExpression(QueueT& queue);
public:
    RPN(std::shared_ptr<MapT const> operators) noexcept;

    double solve(std::string expression);
};
