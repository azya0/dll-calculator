#pragma once

#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <memory>
#include <windows.h>
#include <filesystem>

#include "../../lib/dllData.h"
#include "../types/types.h"

class DllLoader {
private:
    std::vector<HMODULE> loadedModules;
    std::shared_ptr<MapT<Operator>> operators;
    std::shared_ptr<MapT<UnaryOperator>> unaryOperators;
public:
    DllLoader(std::string const & directory);
    ~DllLoader();

    std::shared_ptr<PairT> getOperators() const;
};
