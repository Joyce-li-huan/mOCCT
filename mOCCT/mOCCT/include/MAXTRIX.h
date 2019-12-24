#ifndef _MAXTRIX_HEADER_
#define _MAXTRIX_HEADER_


#include "gmath.h"
#include "basics.h"

//class VECTOR3d;

//	齐次变换矩阵
typedef struct GMATH_API tagMATRIX4d
{
	double e[16];
}MATRIX4d;

const MATRIX4d GMATH_API identity_matrix();

//	同OpenGL一致，对点右乘
const MATRIX4d GMATH_API rotate_matrix(double angle, unsigned int iAxle);

MATRIX4d GMATH_API extract_rotate_matrix(MATRIX4d m);

const MATRIX4d GMATH_API translate_matrix(VECTOR3d delta);

const MATRIX4d GMATH_API translate_matrix(double dx, double dy, double dz);

const VECTOR3d GMATH_API matrix_col(MATRIX4d m, int i);

const VECTOR4d GMATH_API matrix_col_full(MATRIX4d m, int i);

const VECTOR3d GMATH_API matrix_row(MATRIX4d m, int i);

const VECTOR4d GMATH_API matrix_row_full(MATRIX4d m, int i);

const MATRIX4d GMATH_API matrix(VECTOR3d u, VECTOR3d v, VECTOR3d w);

const MATRIX4d GMATH_API matrix(double* e);

void GMATH_API set_matrix_row(MATRIX4d& m, VECTOR3d u, int i);

void GMATH_API set_matrix_col(MATRIX4d& m, VECTOR3d u, int i);

//	根据镜向平面得到镜向矩阵，Q与n分别为定义镜面的面上一点和法向
//  
const MATRIX4d GMATH_API mirror_matrix(POINT4d Q, VECTOR4d n);

//	张量积
const MATRIX4d GMATH_API tensor_product(VECTOR4d a, VECTOR4d b);

//	
const MATRIX4d GMATH_API get_dissymmetry_matrix(VECTOR4d a);

//	点或向量绕某轴（Q为轴上点，n为轴向）旋转一个角度
const MATRIX4d GMATH_API general_rotate(POINT4d Q, VECTOR4d n, double angle);


//	对点右乘，不适于对向量
const POINT3d GMATH_API operator *(const POINT3d& b, const MATRIX4d& a);

//	对点右乘
const POINT4d GMATH_API operator *(const POINT4d& b, const MATRIX4d& a);


//	矩阵相乘
const MATRIX4d GMATH_API operator *(const MATRIX4d& a, const MATRIX4d& b);

//	矩阵数乘
const MATRIX4d GMATH_API operator *(const double& k, const MATRIX4d& b);

//	矩阵相减
const MATRIX4d GMATH_API operator -(const MATRIX4d& a, const MATRIX4d& b);

//	矩阵相加
const MATRIX4d GMATH_API operator +(const MATRIX4d& a, const MATRIX4d& b);


#endif