# Calculator with .dll operations

Calculator logic that works with **any** operators written in .dll

## How to use it?

1. Download the latest release, or build it yourself from the source files and the cmake build system

For example, commands for Windows (using [ninja](https://ninja-build.org/)):

```
cmake -B ./.build -G Ninja
cd ./.build
ninja
```

2. Run the compiled file, for example:

```
.\calculator.exe
```

3. Write a mathematical expression in the console and get the answer:

```
1 - sin(-5 + (-6)^2) / 10 + !2
> 3.0404
```

## How to write .dll?

1. Use [dllScheme.h](https://github.com/azya0/dll-calculator/blob/main/lib/dllScheme.h)

```
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
```

2. Include it to your code

```
#include "../dllScheme.h"
```

3. Write ***REQUIRED*** functions:

```
Data LIBRARY_EXPORT getData() noexcept
```
```
void doMath(StackT& stack)
```

4. Use [references](https://github.com/azya0/dll-calculator/blob/main/lib/addition/add.cpp)

5. Don't forget to pre-assemble the libraries
