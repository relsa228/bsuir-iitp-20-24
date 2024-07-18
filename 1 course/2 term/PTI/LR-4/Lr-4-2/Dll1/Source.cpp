#include "pch.h"
#include <iostream>
#include <math.h>
#include "Header.h"
using namespace std;

int add(int fNum, int sNum)
{
    return fNum + sNum;
}

int minus(int fNum, int sNum)
{
    return fNum - sNum;
}

int divided(int fNum, int sNum)
{
    if (sNum == 0)
        return 0;
    return fNum / sNum;
}

int multiply(int fNum, int sNum)
{
    return fNum * sNum;
}

int power(int fNum, int sNum)
{
    return pow(fNum, sNum);
}

