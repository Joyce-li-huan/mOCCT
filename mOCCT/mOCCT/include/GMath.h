#pragma once
#ifdef GMATH_EXPORTS
#define GMATH_API _declspec(dllexport)
#else
#define GMATH_API _declspec(dllimport)
#endif 


GMATH_API int fnGMath(int a,int b);

