// basics.h

#pragma once

#include <vector>
#include <list>
//#include "..\gmath.h"
#include"GMath.h"
//#include "gmath.h"

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

using namespace std;

typedef struct GMATH_API tagPOINT2d
{
	double x, y;
}POINT2d;

typedef struct GMATH_API tagPOINT3d
{
	double x, y, z;
}POINT3d;

typedef struct GMATH_API tagPOINT4d
{
	double x, y, z, w;
}POINT4d;

template class GMATH_API std::allocator<POINT3d*>;
template class GMATH_API std::vector<POINT3d*, std::allocator<POINT3d*>>;


typedef GMATH_API std::vector<POINT3d*>		PointArray;
typedef GMATH_API PointArray VectorArray;

typedef POINT2d VECTOR2d;
typedef POINT3d VECTOR3d;
typedef POINT4d VECTOR4d;

void GMATH_API copy_point(POINT3d*& a, POINT3d*& b);
void GMATH_API copy_point(POINT3d& a, POINT3d& b);
void GMATH_API copy_point(POINT4d& a, POINT3d b);
void GMATH_API copy_point(POINT3d& a, POINT4d b);
void GMATH_API copy_vector(VECTOR4d& a, VECTOR3d b);


//  
//	向量相加
VECTOR3d GMATH_API operator +(VECTOR3d a, VECTOR3d b);
VECTOR2d GMATH_API operator +(VECTOR2d a, VECTOR2d b);

//	点与点相减
VECTOR3d GMATH_API operator -(POINT3d a, POINT3d b);
VECTOR2d GMATH_API operator -(POINT2d a, POINT2d b);

//	向量数乘
VECTOR3d GMATH_API operator *(double a, VECTOR3d b);
VECTOR2d GMATH_API operator *(double a, VECTOR2d b);

//	向量叉乘
VECTOR3d GMATH_API operator *(VECTOR3d a, VECTOR3d b);

const VECTOR3d GMATH_API operator-(const VECTOR3d& a);
const VECTOR2d GMATH_API operator-(const VECTOR2d& a);


//	向量点乘
double dot(const VECTOR4d& a, const VECTOR4d& b);
double GMATH_API dot(VECTOR3d a, VECTOR3d b);
double GMATH_API dot(VECTOR2d a, VECTOR2d b);

//	向量叉乘
VECTOR3d GMATH_API cross(VECTOR3d a, VECTOR3d b);

//	点与点的距离
double GMATH_API _distance(POINT2d a, POINT2d b);
double GMATH_API _distance(POINT3d a, POINT3d b);

//	向量长度
double GMATH_API length(VECTOR2d v);
double GMATH_API length(VECTOR3d b);

//	单位化向量
VECTOR2d GMATH_API normalise(VECTOR2d v);
VECTOR3d GMATH_API normalise(VECTOR3d v);
void GMATH_API normalise(double& a, double& b, double& c);

//////////////////////////////////////////////////////////////////////////
//	构造POINT3d
POINT3d	GMATH_API position(double x, double y, double z);
POINT3d	GMATH_API point(double x, double y, double z);
POINT3d GMATH_API point(POINT2d p, double z);
POINT3d GMATH_API point(POINT4d p);


//	构造POINT4d
POINT4d	GMATH_API point(double x, double y, double z, double w);
POINT4d GMATH_API point(POINT3d p, double w);


//	判断是否为同一点
bool GMATH_API is_same_point(POINT2d a, POINT2d b);
bool GMATH_API is_same_point(POINT3d a, POINT3d b);

//	判断两矢量是否平行
bool GMATH_API is_parall_vectors(VECTOR2d a, VECTOR2d b);
bool GMATH_API is_parall_vectors(VECTOR3d a, VECTOR3d b);

//	得到与某向量正交的其它两向量
void GMATH_API get_ortho_vectors(VECTOR3d w, VECTOR3d& u, VECTOR3d& v);

//	平移点（集）
void GMATH_API transf_point(double &x,double &y,double &z,double x1,double y1,double z1);
void GMATH_API transf_point(double &x,double &y,double &z,double x1,double y1,double z1);
POINT3d GMATH_API transf_point(POINT3d pt, VECTOR3d dv);
PointArray GMATH_API transf_points(PointArray pts, VECTOR3d dv);

//	旋转点（集）
void GMATH_API rotate_point(double &x,double &y,double &z, double angle, bool axis_x, bool axis_y, bool axis_z);
void GMATH_API rotate_point(double &x,double &y,double &z, double angle, bool axis_x, bool axis_y, bool axis_z);
POINT3d GMATH_API rotate_point(POINT3d pt, double angle, bool axis_x, bool axis_y, bool axis_z);
PointArray GMATH_API rotate_points(PointArray pts, double angle, bool axis_x, bool axis_y, bool axis_z);

/*(sp-op)*(ep-op)的叉积
r=multiply(sp,ep,op),得到(sp-op)*(ep-op)的叉积
r>0:sp在矢量op ep的顺时针方向；
r=0：op sp ep三点共线；
r<0: sp在矢量op ep的逆时针方向 */
double GMATH_API multiply(POINT2d sp,POINT2d ep,POINT2d op);


/////////////////////////////////////////////////////////////////
int GMATH_API agaus(double* a,double* b,int n);

