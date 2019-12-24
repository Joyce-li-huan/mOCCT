
#pragma once
#ifdef GMATH_EXPORTS
#define GMATH_API _declspec(dllexport)
#else
#define GMATH_API _declspec(dllimport)
#endif 
#include"GMath.h"


GMATH_API int add(int a, int b);