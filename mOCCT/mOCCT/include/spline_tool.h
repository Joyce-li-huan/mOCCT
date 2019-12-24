//////////////////////////////////////////////////////////////////////////
//	spline_tool.h

#pragma once

#include "GMath.h"
#include "geometry.h"
#include "basics.h"

typedef struct GMATH_API tagSPLINE_CURVE 
{
	PointArray& ctrlPts;
	std::vector<double> knots;
	bool bClosed;
}SPLINE_CURVE;


bool GMATH_API get_pts_spline_curve(const PointArray& pts, PLANE& plane, SPLINE_CURVE, bool isClosed);
