#include "add.h"


Data LIBRARY_EXPORT getData() noexcept {
    return {"+", 0, 2};
}

double doMath(std::vector<double>& data) {
    if (data.size() < 2) {
        throw std::runtime_error("Additional function has lower than 2 value");
    }

    return data[0] + data[1];
}
