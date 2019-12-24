//////////////////////////////////////////////////////////////////////////
//

#pragma once

#include "fitting.h"

//	f(x)是大小为m的向量
//		p为采样点矩阵，为mx3，m为点数
bool GMATH_API cone_f(VEC& f, const MAT& p, const VEC& x);

//	Df(x)为f(x)的雅可比矩阵，大小为m*6
//		p为采样点矩阵，为mx3，m为点数
bool GMATH_API cone_Df(MAT &df, const MAT& p, const VEC& x);

//	sp采样点矩阵
//	xk返回值向量
bool GMATH_API cone_fit_LM(const MAT& sp, VEC& xk);

