////////////////////////////////////////////////////////////////////////////
//	gtool.h

#pragma once

#include "geometry.h"
//#include "..\gmath.h"
#include"GMath.h"
//	得到点集的最小包围球
double GMATH_API get_bounding_sphere(const PointArray& pts, POINT3d& center);

//	重复测距长度
double GMATH_API get_repeat_length(const PointArray& pts);

//	得到点集的中心
bool GMATH_API get_pts_center(const PointArray& pts, POINT3d& center);

//	得到点集的拟合平面
bool GMATH_API get_pts_plane(const PointArray& pts, PLANE& plane);

//	得到点集的拟合直线
bool GMATH_API get_pts_line(const PointArray& pts, LINE3d& line);

//	得到圆柱的初始值，用于LM法迭代
//	minPP为操作过程中上下最大的误差
bool GMATH_API get_pts_initial_cylinder(const PointArray& pts, CYLINDER& cyl, double minPP);

//	得到拟合的圆柱
bool GMATH_API get_pts_cylinder(const PointArray& pts, CYLINDER& cylinder);

//	得到圆锥的初始值，用于LM法迭代
bool GMATH_API get_pts_initial_cone(const PointArray& pts, CONE& cone, double minPP);

//	得到拟合的圆锥
bool GMATH_API get_pts_cone(const PointArray& pts, CONE& cone);

//	根据点集在XOY平面的映射拟合平面圆
bool GMATH_API get_pts_circle(const PointArray& pts, PLANE& plane,CIRCLE2d& circle);

//	不用圆的采样点作拟合平面的点，即，圆所在平面已知
bool GMATH_API get_pts_circle3(const PointArray& pts, const PLANE& plane, VECTOR3d u, VECTOR3d v, CIRCLE2d& circle, double& roundness);

//	用圆的采样点作拟合平面的点，即，圆所在平面已知
bool GMATH_API get_pts_circle2(const PointArray& pts,PLANE& plane, CIRCLE2d& circle, double& roundness);

bool GMATH_API get_pts_circle(const PointArray& pts, CIRCLE2d& circle);

//得到点集的平面直线
bool GMATH_API get_pts_line_on_plane(const PointArray& pts, const PLANE& plane, LINE3d& line, double& straightness, POINT3d* end);

//  得到点集的拟合球面
bool GMATH_API get_pts_sphere(const PointArray& pts, SPHERE& sphere);

//  得到点集的拟合圆环面
bool GMATH_API get_pts_torus(const PointArray& pts, TORUS& torus);

//  对定位点的测量点集进行SPAT评价
void GMATH_API evaluate_spat(const PointArray& pts, POINT3d& average, double& max_sigma, double& sigma);

//	对长度的空间性能评价
void GMATH_API evaluate_volume_performance(const PointArray& pts, double& norminal, double& max_deviation, double& deviation_range, double& sigma);
