/*
 * This file is part of the OBCD (Object Branching Control Delegation) distribution
 * (https://github.com/peads/obcd).
 * Copyright (c) 2026 Patrick Eads.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <stdio.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

typedef struct $ProducerInfo
{
    FARPROC producer;
    const char *name;
} ProducerInfo;

int main()
{
    const HMODULE module = LoadLibrary("dwmapi.dll");
    if (!module)
        return -1;

    char dllPath[MAX_PATH];
    GetModuleFileName(module, dllPath, MAX_PATH);
    char systemDir[MAX_PATH];
    GetSystemDirectory(systemDir, MAX_PATH);

    printf("Actual dll loaded: %s\nMost likely expected dll due to pragma import: %s\\%s\nheh heh\n",
           dllPath, systemDir, "dwmapi.dll");
    const ProducerInfo producers[2] = {
        {.producer = GetProcAddress(module, "DwmFlush"), .name = "DwmFlush"},
        {.producer = GetProcAddress(module, "DllCanUnloadNow"), .name = "DllCanUnloadNow"}
    };

    long long result = 0;
    for (size_t i = 0; i < 2; ++i)
    {
        result |= producers[i].producer();
        printf("%s: %s\n", producers[i].name, result != S_OK ? "FAIL" : "S_OK");
    }
    return (int)result;
}
