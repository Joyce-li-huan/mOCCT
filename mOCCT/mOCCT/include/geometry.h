//////////////////////////////////////////////////////////////////////////
//  geometry.h

#pragma once

#include "basics.h"
//#include "..\gmath.h"
#include"GMath.h"
/************************************************************************/
/*                       构造几何结构                                   */
/************************************************************************/

//	二维直线类
typedef struct GMATH_API tagLINE2d{
	VECTOR2d normal;		//	平面直线方向
	POINT2d  P;			//	平面直线上一点
}LINE2d;

//	三维直线类
typedef struct GMATH_API tagLINE3d{
	VECTOR3d normal;		//	空间直线方向
	POINT3d  P;			//	空间直线上一点
}LINE3d;

//	平面
typedef struct GMATH_API tagPLANE{
	POINT3d		P;			//	平面上一点
	VECTOR3d	normal;		//	平面法向
}PLANE;

//  空间平面直线类
typedef struct GMATH_API tagPLANE_LINE{
	LINE3d   line;           //三维直线
	VECTOR3d normal;   //直线所在平面法向向量
}PLANE_LINE;

//	圆类
typedef struct GMATH_API tagCIRCLE2d{
	POINT2d  center;			//	圆心
	double	 r;				//	直径
}CIRCLE2d;

//  空间平面圆类
typedef struct GMATH_API tagCIRCLE3d{
	POINT3d   center;          //圆心
	double    r;               //半径
	VECTOR3d  normal;          //圆所在平面法向向量
}CIRCLE3d;

//	椭圆
typedef struct GMATH_API tagELLIPSE2d{
	POINT2d  	center;		//	椭圆中心
	VECTOR2d	u,v;			//	长短轴的方向
	double 		a,b;			//	长短轴的长度
}ELLIPSE2d;

//	柱面
typedef struct GMATH_API tagCYLINDER{
	LINE3d		axis;			//	圆柱中心
	double		r;			//	圆柱半径
}CYLINDER;

//	球面
typedef struct GMATH_API tagSPHERE{
	POINT3d 	center;		//	球心
	double 		r;			//	球半径
}SPHERE;


//	锥面
typedef struct GMATH_API tagCONE{
	LINE3d		axis;			//	圆锥轴线
	double      s;          //  P点到圆锥的正交距离
	double      a;          //  圆锥顶点半角
}CONE;

//	环面
typedef struct GMATH_API tagTORUS{
	LINE3d      axis;
	double 		r;			//	环小径
	double      R;          //  环大径
}TORUS;

void GMATH_API copy_plane(PLANE& a, PLANE& b);

//////////////////////////////////////////////////////////////////////////
//	构造直线
LINE3d GMATH_API make_line(POINT3d p1, POINT3d p2);	//	以p1为点，p2-p2为方向构造直线

//////////////////////////////////////////////////////////////////////////
//	点到平面直线的投影
double GMATH_API project_pt_to_line2d(POINT2d pt, LINE2d, POINT2d& ppt);

//	点到空间直线的投影
double GMATH_API project_pt_to_line3d(POINT3d pt, LINE3d line, POINT3d& ppt);

//	点到平面的投影
POINT3d GMATH_API project_pt_to_plane(POINT3d pt, PLANE plane);

//	直线到平面的投影
LINE3d GMATH_API project_line_to_plane(LINE3d line, PLANE plane);

//	点到柱面的投影
POINT3d GMATH_API project_pt_to_cylinder(POINT3d pt, CYLINDER cylinder);

//	点到球面的投影
POINT3d GMATH_API project_pt_to_sphere(POINT3d pt, SPHERE sphere);

//	点到平面直线的距离
double GMATH_API _distance(POINT2d, LINE2d line);

double GMATH_API _distance(POINT2d pt1,POINT2d pt2,POINT2d pt3);

//  点到平面直线的距离
double GMATH_API _distance(POINT2d pt1,POINT2d pt2,POINT2d pt3);

//	点到空间直线的距离
double GMATH_API _distance(POINT3d, LINE3d line);

//	点到平面的距离
double GMATH_API _distance(POINT3d, PLANE plane);

//	点到柱面的距离
double GMATH_API _distance(POINT3d, CYLINDER cylinder);

//	点到球面的距离
double GMATH_API _distance(POINT3d, SPHERE sphere);

//	线与线角度，弧度
double GMATH_API _angle(LINE3d line1, LINE3d line2);

//	线与面角度，指的是线与面的夹角，而非线与法线的夹角，弧度
double GMATH_API _angle(LINE3d line1, PLANE plane);

//	面与面角度
double GMATH_API _angle(PLANE plane1, PLANE plane2);


//	直线与平面的交点
POINT3d GMATH_API intersection_line_plane(LINE3d line, PLANE plane);


//	平面与平面的交线
LINE3d GMATH_API intersection_plane_plane(PLANE plane1, PLANE plane2);
