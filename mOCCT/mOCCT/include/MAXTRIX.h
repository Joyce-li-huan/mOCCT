#ifndef _MAXTRIX_HEADER_
#define _MAXTRIX_HEADER_


#include "gmath.h"
#include "basics.h"

//class VECTOR3d;

//	��α任����
typedef struct GMATH_API tagMATRIX4d
{
	double e[16];
}MATRIX4d;

const MATRIX4d GMATH_API identity_matrix();

//	ͬOpenGLһ�£��Ե��ҳ�
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

//	���ݾ���ƽ��õ��������Q��n�ֱ�Ϊ���徵�������һ��ͷ���
//  
const MATRIX4d GMATH_API mirror_matrix(POINT4d Q, VECTOR4d n);

//	������
const MATRIX4d GMATH_API tensor_product(VECTOR4d a, VECTOR4d b);

//	
const MATRIX4d GMATH_API get_dissymmetry_matrix(VECTOR4d a);

//	���������ĳ�ᣨQΪ���ϵ㣬nΪ������תһ���Ƕ�
const MATRIX4d GMATH_API general_rotate(POINT4d Q, VECTOR4d n, double angle);


//	�Ե��ҳˣ������ڶ�����
const POINT3d GMATH_API operator *(const POINT3d& b, const MATRIX4d& a);

//	�Ե��ҳ�
const POINT4d GMATH_API operator *(const POINT4d& b, const MATRIX4d& a);


//	�������
const MATRIX4d GMATH_API operator *(const MATRIX4d& a, const MATRIX4d& b);

//	��������
const MATRIX4d GMATH_API operator *(const double& k, const MATRIX4d& b);

//	�������
const MATRIX4d GMATH_API operator -(const MATRIX4d& a, const MATRIX4d& b);

//	�������
const MATRIX4d GMATH_API operator +(const MATRIX4d& a, const MATRIX4d& b);


#endif