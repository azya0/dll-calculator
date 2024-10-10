#include "dll_loader.h"

template<typename T>
T getFunction(HMODULE module, const char * functionName) {
    auto function = (T)GetProcAddress(module, functionName);

    if (!function) {
        throw std::runtime_error("has no " + std::string(functionName) + " function");
    }

    return function;
}

template<typename vT, typename fT>
vT getValue(HMODULE module, const char * functionName, std::string& path) {
    try {
        vT value = getFunction<fT>(module, functionName)();

        return value;
    } catch (std::exception& error) {
        throw std::runtime_error(path + " module " + error.what());
    }
}

DllLoader::DllLoader(std::string const &directory) {
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".dll") {
            std::string path = entry.path().string();
            // без std::wstring он не хочет принимать path.c_str()
            std::wstring wpath = std::wstring(path.begin(), path.end());
            HMODULE hModule = LoadLibraryW(wpath.c_str());
            
            if (!hModule) {
                throw std::runtime_error("can't load " + path);
            }

            loadedModules.push_back(hModule);

            Data data = getValue<Data, Data(*)()>(
                hModule, "getData", path
            );

            auto function = getFunction<double (*)(std::vector<double>&)>(hModule, "doMath");

            (*operators)[data.value] = std::make_shared<Operator>(Operator(
                std::make_shared<std::function<double(std::vector<double>&)>>(function),
                data.priority, data.valueRequire
            ));
        }
    }
}

DllLoader::~DllLoader() {
    for (auto hModule : loadedModules) {
        FreeLibrary(hModule);
    }
}

std::shared_ptr<MapT const> DllLoader::getOperators() const {
    return std::make_shared<MapT const>(*operators);
}
