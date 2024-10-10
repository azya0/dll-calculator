#include "deduction.h"

Data LIBRARY_EXPORT getData() noexcept {
    return {"/", 1, 2};
}

double doMath(std::vector<double>& data) {
    if (data.size() < 2) {
        throw std::runtime_error("Deductional function has lower than 2 value");
    }

    if (data[0] == 0) {
        throw std::runtime_error("Zero deductional");
    }

    return data[1] / data[0];
}
