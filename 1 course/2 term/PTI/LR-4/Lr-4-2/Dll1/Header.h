#pragma once

#ifdef DLL_EXPORTS
#define DLL __declspec(dllexport)
#else
#define Math __declspec(dllimport)
#endif

extern "C" Math int add(int fNum, int sNum);
extern "C" Math int minus(int fNum, int sNum);
extern "C" Math int divided(int fNum, int sNum);
extern "C" Math int multiply(int fNum, int sNum);
extern "C" Math int power(int fNum, int sNum);
