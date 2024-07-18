#pragma once

#ifdef DLL_EXPORTS
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif

extern "C" DLL void PereborSchet(int* arr, int str);

extern "C" DLL void PrintArray(int* arr, const int sqr1);

extern "C" DLL void FillArray(int* arr, const int sqr1);