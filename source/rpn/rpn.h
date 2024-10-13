#include <string>
#include <memory>
#include <queue>
#include <unordered_map>

#include "../types/types.h"

class RPN {
private:
    using QueueT = std::queue<std::shared_ptr<Token>>;
    using OperT = std::pair<bool, std::shared_ptr<UnaryOperator>>;

    PairT& operators;
    std::string expression;

    void emptyBrackets(std::stack<OperT>& stack, QueueT& queue, bool wasDigit) const;

    std::shared_ptr<UnaryOperator> getOperator(std::string const & substr, bool isUnar) const;

    std::shared_ptr<Value> parseNumber(int& index) const;

    std::shared_ptr<OperT> parseOperator(int& index, bool wasDigit) const;

    std::shared_ptr<QueueT> buildExpression() const;

    double solveExpression(QueueT& queue) const;
public:
    RPN(PairT& operators) noexcept;

    double solve(std::string expression);
};
