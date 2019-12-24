//////////////////////////////////////////////////////////////////////////
//  geometry.h

#pragma once

#include "basics.h"
//#include "..\gmath.h"
#include"GMath.h"
/************************************************************************/
/*                       ���켸�νṹ                                   */
/************************************************************************/

//	��άֱ����
typedef struct GMATH_API tagLINE2d{
	VECTOR2d normal;		//	ƽ��ֱ�߷���
	POINT2d  P;			//	ƽ��ֱ����һ��
}LINE2d;

//	��άֱ����
typedef struct GMATH_API tagLINE3d{
	VECTOR3d normal;		//	�ռ�ֱ�߷���
	POINT3d  P;			//	�ռ�ֱ����һ��
}LINE3d;

//	ƽ��
typedef struct GMATH_API tagPLANE{
	POINT3d		P;			//	ƽ����һ��
	VECTOR3d	normal;		//	ƽ�淨��
}PLANE;

//  �ռ�ƽ��ֱ����
typedef struct GMATH_API tagPLANE_LINE{
	LINE3d   line;           //��άֱ��
	VECTOR3d normal;   //ֱ������ƽ�淨������
}PLANE_LINE;

//	Բ��
typedef struct GMATH_API tagCIRCLE2d{
	POINT2d  center;			//	Բ��
	double	 r;				//	ֱ��
}CIRCLE2d;

//  �ռ�ƽ��Բ��
typedef struct GMATH_API tagCIRCLE3d{
	POINT3d   center;          //Բ��
	double    r;               //�뾶
	VECTOR3d  normal;          //Բ����ƽ�淨������
}CIRCLE3d;

//	��Բ
typedef struct GMATH_API tagELLIPSE2d{
	POINT2d  	center;		//	��Բ����
	VECTOR2d	u,v;			//	������ķ���
	double 		a,b;			//	������ĳ���
}ELLIPSE2d;

//	����
typedef struct GMATH_API tagCYLINDER{
	LINE3d		axis;			//	Բ������
	double		r;			//	Բ���뾶
}CYLINDER;

//	����
typedef struct GMATH_API tagSPHERE{
	POINT3d 	center;		//	����
	double 		r;			//	��뾶
}SPHERE;


//	׶��
typedef struct GMATH_API tagCONE{
	LINE3d		axis;			//	Բ׶����
	double      s;          //  P�㵽Բ׶����������
	double      a;          //  Բ׶������
}CONE;

//	����
typedef struct GMATH_API tagTORUS{
	LINE3d      axis;
	double 		r;			//	��С��
	double      R;          //  ����
}TORUS;

void GMATH_API copy_plane(PLANE& a, PLANE& b);

//////////////////////////////////////////////////////////////////////////
//	����ֱ��
LINE3d GMATH_API make_line(POINT3d p1, POINT3d p2);	//	��p1Ϊ�㣬p2-p2Ϊ������ֱ��

//////////////////////////////////////////////////////////////////////////
//	�㵽ƽ��ֱ�ߵ�ͶӰ
double GMATH_API project_pt_to_line2d(POINT2d pt, LINE2d, POINT2d& ppt);

//	�㵽�ռ�ֱ�ߵ�ͶӰ
double GMATH_API project_pt_to_line3d(POINT3d pt, LINE3d line, POINT3d& ppt);

//	�㵽ƽ���ͶӰ
POINT3d GMATH_API project_pt_to_plane(POINT3d pt, PLANE plane);

//	ֱ�ߵ�ƽ���ͶӰ
LINE3d GMATH_API project_line_to_plane(LINE3d line, PLANE plane);

//	�㵽�����ͶӰ
POINT3d GMATH_API project_pt_to_cylinder(POINT3d pt, CYLINDER cylinder);

//	�㵽�����ͶӰ
POINT3d GMATH_API project_pt_to_sphere(POINT3d pt, SPHERE sphere);

//	�㵽ƽ��ֱ�ߵľ���
double GMATH_API _distance(POINT2d, LINE2d line);

double GMATH_API _distance(POINT2d pt1,POINT2d pt2,POINT2d pt3);

//  �㵽ƽ��ֱ�ߵľ���
double GMATH_API _distance(POINT2d pt1,POINT2d pt2,POINT2d pt3);

//	�㵽�ռ�ֱ�ߵľ���
double GMATH_API _distance(POINT3d, LINE3d line);

//	�㵽ƽ��ľ���
double GMATH_API _distance(POINT3d, PLANE plane);

//	�㵽����ľ���
double GMATH_API _distance(POINT3d, CYLINDER cylinder);

//	�㵽����ľ���
double GMATH_API _distance(POINT3d, SPHERE sphere);

//	�����߽Ƕȣ�����
double GMATH_API _angle(LINE3d line1, LINE3d line2);

//	������Ƕȣ�ָ����������ļнǣ��������뷨�ߵļнǣ�����
double GMATH_API _angle(LINE3d line1, PLANE plane);

//	������Ƕ�
double GMATH_API _angle(PLANE plane1, PLANE plane2);


//	ֱ����ƽ��Ľ���
POINT3d GMATH_API intersection_line_plane(LINE3d line, PLANE plane);


//	ƽ����ƽ��Ľ���
LINE3d GMATH_API intersection_plane_plane(PLANE plane1, PLANE plane2);
