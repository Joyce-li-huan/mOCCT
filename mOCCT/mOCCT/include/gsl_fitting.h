//////////////////////////////////////////////////////////////////////////
//	gsl_fitting.h

#include "geometry.h"
//#include "..\gmath.h"
#include"GMath.h"

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_multifit_nlin.h>
#include<gsl/gsl_vector_double.h>

using namespace std;

#ifndef ZERO
#define ZERO 0.000001
#endif


bool GMATH_API get_gsl_circle(const PointArray& pts, CIRCLE2d& circle);
bool GMATH_API get_gsl_cylinder(const PointArray& pts, CYLINDER& cylinder);
bool GMATH_API get_gsl_cone(const PointArray& pts, CONE& cone);
bool GMATH_API get_gsl_sphere(const PointArray& pts, SPHERE& sphere);

struct data2D {
	size_t n;
	double * x;
	double * y;
};

struct data3D {
	size_t n;
	double * x;
	double * y;
	double * z;
};


//////////////////////////////////////////////////////////////////////////

int circle2D_f(const gsl_vector * x, void *params, gsl_vector * f);
int circle2D_df (const gsl_vector * x, void *params, gsl_matrix * J);
int circle2D_fdf (const gsl_vector * x, void *params, gsl_vector * f, gsl_matrix * J);

//////////////////////////////////////////////////////////////////////////

int cylinder_f (const gsl_vector * x, void *data, gsl_vector * f);
int cylinder_df (const gsl_vector * x, void *data, gsl_matrix * J);
int cylinder_fdf (const gsl_vector * x, void *data, gsl_vector * f, gsl_matrix * J);

//////////////////////////////////////////////////////////////////////////

int cylinder_f (const gsl_vector * x, void *data, gsl_vector * f);
int cylinder_df (const gsl_vector * x, void *data, gsl_matrix * J);
int cylinder_fdf (const gsl_vector * x, void *data, gsl_vector * f, gsl_matrix * J);
