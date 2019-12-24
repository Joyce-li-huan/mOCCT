//////////////////////////////////////////////////////////////////////////
//

#pragma once

#include "fitting.h"

//	f(x)�Ǵ�СΪm������
//		pΪ���������Ϊmx3��mΪ����
//		p0ΪԲ��������һ��
//		alpha��beta��������Բ�����߷���
//		rΪԲ��ֱ��
bool GMATH_API cylinder_f(VEC& f, const MAT& p, const VEC& x);

//	Df(x)Ϊf(x)���ſɱȾ��󣬴�СΪm*6
//		pΪ���������Ϊmx3��mΪ����
//		p0ΪԲ��������һ��
//		alpha��beta��������Բ�����߷���
//		rΪԲ��ֱ��
bool GMATH_API cylinder_Df(MAT &df, const MAT& p, const VEC& x);

//	sp���������
//	xk����ֵ����
bool GMATH_API cylinder_fit_LM(const MAT& sp, VEC& xk);


//	sp���������
//	x����ֵ����
bool cylinder_estimate(const MAT& sp, VEC& x);


