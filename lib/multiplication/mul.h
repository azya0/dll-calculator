#ifndef FILE_H
#define FILE_H

#if defined(MYLIBRARY)
    #define LIBRARY_EXPORT __declspec(dllexport)
#else
    #define LIBRARY_EXPORT
#endif

#include <stdexcept>
#include <vector>

extern "C" const char* LIBRARY_EXPORT  getValue() noexcept;
extern "C" unsigned char LIBRARY_EXPORT  getPriority() noexcept;
extern "C" unsigned char LIBRARY_EXPORT  valueRequire() noexcept;
extern "C" double LIBRARY_EXPORT doMath(std::vector<double>& data);

#endif
