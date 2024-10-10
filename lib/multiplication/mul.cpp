#include "mul.h"

Data LIBRARY_EXPORT getData() noexcept {
    return {"*", 1, 2};
}

double doMath(std::vector<double>& data) {
    if (data.size() < 2) {
        throw std::runtime_error("Multiplicational function has lower than 2 value");
    }

    return data[0] * data[1];
}
