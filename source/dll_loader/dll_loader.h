#pragma once

#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <memory>
#include <windows.h>
#include <filesystem>
#include <string>

#include "../interface/interfaces.h"

using MapT = std::unordered_map<std::string, std::shared_ptr<Operator>>;

typedef struct data {
    const char * value;
    unsigned char priority;
    unsigned char valueRequire;
} Data;

class DllLoader {
private:
    std::vector<HMODULE> loadedModules;
    std::shared_ptr<MapT> operators = std::make_shared<MapT>();
public:
    DllLoader(std::string const & directory);
    ~DllLoader();

    std::shared_ptr<MapT const> getOperators() const;
};
