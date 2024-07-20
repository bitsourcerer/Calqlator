// dllmain.cpp : Defines the entry point for the DLL application.
#include <cstdlib>
#include <cstdio>
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"

#ifdef _WIN32
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
#ifndef NDEBUG
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif // NDEBUG
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#else
int main()
{
    return EXIT_SUCCESS;
}
#endif
