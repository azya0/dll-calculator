#ifndef FILE_H
#define FILE_H

#if defined(MYLIBRARY)
    #define LIBRARY_EXPORT __declspec(dllexport)
#else
    #define LIBRARY_EXPORT
#endif

#include <stdexcept>
#include <vector>

#include "dllData.h"
#include "../interface/interfaces.h"

extern "C" Data LIBRARY_EXPORT getData() noexcept;
extern "C" void LIBRARY_EXPORT doMath(StackT& data);

#endif
