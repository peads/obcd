# OBCD - Object Branching Control Delegation
## Description
This utility provides a Windows-compatible, cross-architecture (x86-64 and arm64) capable way to build an intermediate 
shared library (DLL) that exposes every exported symbol of a desired library for transparent pass-through access, and allows loading other libraries at run-time.
This newly produced library seamlessly delegates all calls to the functions exposed by the target library while being able to import an arbitrary number of 
other, user-specified libraries read from a settings file. Depending on the end-use requirement, x86-64, or arm64 assembly code is generated for   
## Use-case(s)
Games modification, extending functionality of (relatively) stable programs, etc.
## Nominal Build Environment
- Windows
- A C++ development environment, e.g., [Microsoft Visual Studio 2019 or later](https://visualstudio.microsoft.com/downloads/)
- [CMake](https://cmake.org/download/)
- **At least one** of the following:
  1. [clang-cl](https://learn.microsoft.com/en-us/cpp/build/clang-support-msbuild?view=msvc-170)
  1. [NASM](https://www.nasm.us) 

**N.B., without clang-cl, the cross-compiling preset will not work. MASM and ARMASM are not supported**
## Basic Build and Use
1. Clone the repo
1. `cd /path/to/obcd`
1. `cmake -S . -B build -DDLL_NAME="/path/to/dll/to/be/procurated.dll"`
   - For clang, instead use: `cmake -S . -B build -T ClangCL ...`
   - If using Ninja instead: `cmake -G Ninja -S . -B build -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl ...`
1. `cmake --build build`
1. Find in the target output directory (here: `/path/to/obcd/build`) an identically-named dll (here: `procurated.dll`) 
to the one provided via `DLL_NAME`.
1. Place this in the root directory (i.e. the same directory as the `.exe`) of the program you wish to load it.
1. Create a file in that same directory called `dlls.txt` with a newline-separated list of the path(s) to whichever dll(s) you wish the dll just moved to load. 
## Build (cross-compile, host: x64, target: arm64)
### Currently, clang-cl is supported
As above, but replace configure step with: `cmake --preset=x64-arm64-cross-compile ...`
## Build the provided example (piggy)
1. As above, but replace configure step with: `cmake --preset=x64-ninja-clangcl ...`
Now, there should be a file located at `/path/to/build/output/bootstrapper/dllloader.exe` that, when run, will load `dwmapi.dll`, but since our dll is also called `dwmpai.dll` and is located in the root directory of the `.exe` it will load that instead of the one (typically) in `C:\Windows\system32\`. The `dlls.txt` file will have the path to another dll produced for this test called `piggy.dll`, which will print its message at load and unload. Meanwhile, `dllloader.exe` calls `DwmFlush` and `DllCanUnloadNow` which are seamlessly passed-through our `dwmapi.dll` to the "real" `dwmapi.dll`.

