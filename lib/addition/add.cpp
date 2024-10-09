#include "add.h"

const char *getValue() noexcept {
    return "+";
}

unsigned char getPriority() noexcept {
    return 0;
}

unsigned char valueRequire() noexcept {
    return 2;
}

double doMath(std::vector<double>& data) {
    if (data.size() < 2) {
        throw std::runtime_error("Additional function has lower than 2 value");
    }

    return data[0] + data[1];
}
