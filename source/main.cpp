#include <iostream>
#include <string>

#include "rpn/rpn.h"
#include "dll_loader/dll_loader.h"

int printException(std::exception& error) {
    std::cout << error.what();
    return 1;
}

int main() {
    std::shared_ptr<DllLoader> loader;
    
    try {
        loader = std::make_shared<DllLoader>("./operators");
    } catch (std::exception& error) {
        return printException(error);
    }

    std::string expression;

    std::getline(std::cin, expression);

    try {
        std::cout << RPN(*loader->getOperators()).solve(expression);
    } catch(std::exception& error) {
        return printException(error);
    }

    return 0;
}
