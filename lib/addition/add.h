#ifndef FILE_H
#define FILE_H

#if defined(MYLIBRARY)
    #define LIBRARY_EXPORT __declspec(dllexport)
#else
    #define LIBRARY_EXPORT
#endif

#include <stdexcept>
#include <vector>

typedef struct data {
    const char * value;
    unsigned char priority;
    unsigned char valueRequire;
} Data;

extern "C" Data LIBRARY_EXPORT getData() noexcept;
extern "C" double LIBRARY_EXPORT doMath(std::vector<double>& data);

#endif
