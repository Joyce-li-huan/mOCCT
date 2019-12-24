//////////////////////////////////////////////////////////////////////////
// fitting.h

#pragma once

#include "..\tnt\tnt.h"
#include <vector>

#include"GMath.h"

#ifndef  _DELTA
#define  _DELTA 0.000001
#endif
#ifndef ZERO
#define ZERO 0.000001
#endif
#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

#ifndef MAX_IERATION
#define MAX_IERATION 99999
#endif

typedef GMATH_API TNT::Vector<double> VEC;
typedef GMATH_API TNT::Matrix<double> MAT;
typedef GMATH_API TNT::Array1D<double> L_VEC;
typedef GMATH_API TNT::Array2D<double> L_MAT;

//////////////////////////////////////////////////////////////////////////
//	Matrix与Array2D，Vector与Array1D之间的相互转换
L_VEC GMATH_API lvec_from_vec(const VEC& x);

L_MAT GMATH_API lmat_from_mat(const MAT& A);

VEC GMATH_API vec_from_lvec(const L_VEC& y);

MAT GMATH_API mat_from_lmat(const L_MAT& S);

//	构造单位阵
L_MAT GMATH_API identity_mat(int n);

//////////////////////////////////////////////////////////////////////////
//	求向量长度
double GMATH_API length(const VEC& x);

double GMATH_API length(const L_VEC& x);

//////////////////////////////////////////////////////////////////////////
//	LU法（高斯消元法）解线性方程组
VEC GMATH_API solve_linear_equation_LU(const MAT& A, const VEC& b);

//void plane_fitting_SVD();

void GMATH_API line_fitting_SVD(const MAT& sp, VEC& s);

void GMATH_API plane_fitting_SVD(const MAT& sp, VEC& s);

bool GMATH_API cylinder_fit_LM(const MAT& sp, VEC& xk);

void GMATH_API circle_fitting_SVD(const MAT& sp, VEC& x);

L_MAT GMATH_API invert(const L_MAT &M);

