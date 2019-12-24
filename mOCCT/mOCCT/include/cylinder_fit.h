//////////////////////////////////////////////////////////////////////////
//

#pragma once

#include "fitting.h"

//	f(x)是大小为m的向量
//		p为采样点矩阵，为mx3，m为点数
//		p0为圆柱轴线上一点
//		alpha，beta用于描述圆柱轴线方向
//		r为圆柱直径
bool GMATH_API cylinder_f(VEC& f, const MAT& p, const VEC& x);

//	Df(x)为f(x)的雅可比矩阵，大小为m*6
//		p为采样点矩阵，为mx3，m为点数
//		p0为圆柱轴线上一点
//		alpha，beta用于描述圆柱轴线方向
//		r为圆柱直径
bool GMATH_API cylinder_Df(MAT &df, const MAT& p, const VEC& x);

//	sp采样点矩阵
//	xk返回值向量
bool GMATH_API cylinder_fit_LM(const MAT& sp, VEC& xk);


//	sp采样点矩阵
//	x返回值向量
bool cylinder_estimate(const MAT& sp, VEC& x);


