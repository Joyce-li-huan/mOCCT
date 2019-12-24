////////////////////////////////////////////////////////////////////////////
//	gtool.h

#pragma once

#include "geometry.h"
//#include "..\gmath.h"
#include"GMath.h"
//	�õ��㼯����С��Χ��
double GMATH_API get_bounding_sphere(const PointArray& pts, POINT3d& center);

//	�ظ���೤��
double GMATH_API get_repeat_length(const PointArray& pts);

//	�õ��㼯������
bool GMATH_API get_pts_center(const PointArray& pts, POINT3d& center);

//	�õ��㼯�����ƽ��
bool GMATH_API get_pts_plane(const PointArray& pts, PLANE& plane);

//	�õ��㼯�����ֱ��
bool GMATH_API get_pts_line(const PointArray& pts, LINE3d& line);

//	�õ�Բ���ĳ�ʼֵ������LM������
//	minPPΪ���������������������
bool GMATH_API get_pts_initial_cylinder(const PointArray& pts, CYLINDER& cyl, double minPP);

//	�õ���ϵ�Բ��
bool GMATH_API get_pts_cylinder(const PointArray& pts, CYLINDER& cylinder);

//	�õ�Բ׶�ĳ�ʼֵ������LM������
bool GMATH_API get_pts_initial_cone(const PointArray& pts, CONE& cone, double minPP);

//	�õ���ϵ�Բ׶
bool GMATH_API get_pts_cone(const PointArray& pts, CONE& cone);

//	���ݵ㼯��XOYƽ���ӳ�����ƽ��Բ
bool GMATH_API get_pts_circle(const PointArray& pts, PLANE& plane,CIRCLE2d& circle);

//	����Բ�Ĳ����������ƽ��ĵ㣬����Բ����ƽ����֪
bool GMATH_API get_pts_circle3(const PointArray& pts, const PLANE& plane, VECTOR3d u, VECTOR3d v, CIRCLE2d& circle, double& roundness);

//	��Բ�Ĳ����������ƽ��ĵ㣬����Բ����ƽ����֪
bool GMATH_API get_pts_circle2(const PointArray& pts,PLANE& plane, CIRCLE2d& circle, double& roundness);

bool GMATH_API get_pts_circle(const PointArray& pts, CIRCLE2d& circle);

//�õ��㼯��ƽ��ֱ��
bool GMATH_API get_pts_line_on_plane(const PointArray& pts, const PLANE& plane, LINE3d& line, double& straightness, POINT3d* end);

//  �õ��㼯���������
bool GMATH_API get_pts_sphere(const PointArray& pts, SPHERE& sphere);

//  �õ��㼯�����Բ����
bool GMATH_API get_pts_torus(const PointArray& pts, TORUS& torus);

//  �Զ�λ��Ĳ����㼯����SPAT����
void GMATH_API evaluate_spat(const PointArray& pts, POINT3d& average, double& max_sigma, double& sigma);

//	�Գ��ȵĿռ���������
void GMATH_API evaluate_volume_performance(const PointArray& pts, double& norminal, double& max_deviation, double& deviation_range, double& sigma);
