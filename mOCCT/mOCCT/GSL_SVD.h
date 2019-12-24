#pragma once

#ifndef GSLSINGULARVALUEDECOMPOSITION_H
#define GSLSINGULARVALUEDECOMPOSITION_H

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_errno.h>

void linearSolve_SVD(const gsl_matrix * A, const gsl_vector * b, gsl_vector * x);
// GSL_SVD 对话框

class GSL_SVD : public CDialog
{
	DECLARE_DYNAMIC(GSL_SVD)

public:
	GSL_SVD(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~GSL_SVD();

	int SV_decomp(const gsl_matrix * A);
	int SV_decomp_mod(const gsl_matrix * A);
	int SV_decomp_jacobi(gsl_matrix * A);
	int SV_solve(const gsl_vector *b, gsl_vector *x);

	gsl_vector * getVectorS();
	gsl_matrix * getMatrixU();
	gsl_matrix * getMatrixV();

	int trimVectorS(double abseps);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SVD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

private:
	gsl_vector * S;
	gsl_matrix * U;
	gsl_matrix * V;

	void alloc_suv(int rows, int cols);
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
#endif // GSLSINGULARVALUEDECOMPOSITION_H