//////////////////////////////////////////////////////////////////////////
//

#pragma once

#include "fitting.h"

//	f(x)�Ǵ�СΪm������
//		pΪ���������Ϊmx3��mΪ����
bool GMATH_API cone_f(VEC& f, const MAT& p, const VEC& x);

//	Df(x)Ϊf(x)���ſɱȾ��󣬴�СΪm*6
//		pΪ���������Ϊmx3��mΪ����
bool GMATH_API cone_Df(MAT &df, const MAT& p, const VEC& x);

//	sp���������
//	xk����ֵ����
bool GMATH_API cone_fit_LM(const MAT& sp, VEC& xk);

