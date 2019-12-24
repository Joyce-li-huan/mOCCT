// GSL_SVD.cpp: 实现文件
//

#include "stdafx.h"
#include "mOCCT.h"
#include "GSL_SVD.h"
#include "afxdialogex.h"
#include"gsl_SVD.h"
#include"stdio.h"
// GSL_SVD 对话框
#include<conio.h>

IMPLEMENT_DYNAMIC(GSL_SVD, CDialog)

GSL_SVD::GSL_SVD(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DLG_SVD, pParent)
{
	S = NULL;
	U = NULL;
	V = NULL;
}

GSL_SVD::~GSL_SVD()
{
	if (S != NULL)
	{
		gsl_vector_free(S);
		gsl_matrix_free(V);
		gsl_matrix_free(U);
	}
}

void GSL_SVD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GSL_SVD, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &GSL_SVD::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_BUTTON5, &GSL_SVD::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &GSL_SVD::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &GSL_SVD::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &GSL_SVD::OnBnClickedButton4)
END_MESSAGE_MAP()



void linearSolve_SVD(const gsl_matrix * A, const gsl_vector * b, gsl_vector * x)
{
	int rows = A->size1;
	int cols = A->size2;
	gsl_vector * work = gsl_vector_alloc(cols);
	gsl_vector * S = gsl_vector_alloc(cols);
	gsl_matrix * U = gsl_matrix_alloc(rows, cols);;
	gsl_matrix * V = gsl_matrix_alloc(cols, cols);

	gsl_matrix_memcpy(U, A); // 为了不破坏 A 中原始的数据，这里全都拷贝到 U 中

	gsl_linalg_SV_decomp(U, V, S, work);
	gsl_linalg_SV_solve(U, V, S, b, x);

	gsl_vector_free(work);
	gsl_vector_free(S);
	gsl_matrix_free(V);
	gsl_matrix_free(U);
}
int GSL_SVD::trimVectorS(double abseps)
{
	int count = 0;
	for (int i = 0; i < S->size; i++)
	{
		if (fabs(gsl_vector_get(S, i)) < abseps)
		{
			count++;
			gsl_vector_set(S, i, 0);
		}
	}
	return count;
}

gsl_vector * GSL_SVD::getVectorS()
{
	if (S == NULL) return NULL;
	gsl_vector * s = gsl_vector_alloc(S->size);
	gsl_vector_memcpy(s, S);
	return s;
}

gsl_matrix * GSL_SVD::getMatrixU()
{
	if (U == NULL) return NULL;
	gsl_matrix * u = gsl_matrix_alloc(U->size1, U->size2);
	gsl_matrix_memcpy(u, U);
	return u;
}

gsl_matrix * GSL_SVD::getMatrixV()
{
	if (V == NULL) return NULL;
	gsl_matrix * v = gsl_matrix_alloc(V->size1, V->size2);
	gsl_matrix_memcpy(v, V);
	return v;
}

void GSL_SVD::alloc_suv(int rows, int cols)
{
	if (S != NULL)
	{
		gsl_vector_free(S);
		gsl_matrix_free(U);
		gsl_matrix_free(V);
	}
	S = gsl_vector_alloc(cols);
	U = gsl_matrix_alloc(rows, cols);
	V = gsl_matrix_alloc(cols, cols);
}

int GSL_SVD::SV_decomp(const gsl_matrix * A)
{
	int rows = A->size1;
	int cols = A->size2;

	gsl_vector * work = gsl_vector_alloc(cols);

	alloc_suv(rows, cols);
	gsl_matrix_memcpy(U, A); // 为了不破坏 A 中原始的数据，这里全都拷贝到 U 中
	int ret = gsl_linalg_SV_decomp(U, V, S, work);

	gsl_vector_free(work);

	return ret;
}

int GSL_SVD::SV_decomp_mod(const gsl_matrix * A)
{
	int rows = A->size1;
	int cols = A->size2;

	gsl_vector * work = gsl_vector_alloc(cols);
	gsl_matrix *X = gsl_matrix_alloc(cols, cols);

	alloc_suv(rows, cols);
	gsl_matrix_memcpy(U, A); // 为了不破坏 A 中原始的数据，这里全都拷贝到 U 中
	int ret = gsl_linalg_SV_decomp_mod(U, X, V, S, work);

	gsl_matrix_free(X);
	gsl_vector_free(work);

	return ret;
}

int GSL_SVD::SV_decomp_jacobi(gsl_matrix * A)
{
	int rows = A->size1;
	int cols = A->size2;
	alloc_suv(rows, cols);
	gsl_matrix_memcpy(U, A); // 为了不破坏 A 中原始的数据，这里全都拷贝到 U 中
	int ret = gsl_linalg_SV_decomp_jacobi(U, V, S);
	return ret;
}

int GSL_SVD::SV_solve(const gsl_vector *b, gsl_vector *x)
{
	if (U != NULL)
	{
		return gsl_linalg_SV_solve(U, V, S, b, x);
	}
	return -1;
}

//Test1
void GSL_SVD::OnBnClickedButton1()
{
	double a_data[] = { 1.4,2.1,2.1,7.4,9.6,
						1.6,1.5,1.1,0.7,5.0,
						3.8,8.0,9.6,5.4,8.8,
						4.6,8.2,8.4,0.4,8.0,
						2.6,2.9,0.1,9.9,7.7 };
	gsl_matrix_view A = gsl_matrix_view_array(a_data,5,5);

	double b_data[] = {1.1,1.6,4.7,9.1,0.1};
	gsl_vector_view b = gsl_vector_view_array(b_data,5);

	gsl_vector * x = gsl_vector_alloc(5);

	linearSolve_SVD(&A.matrix,&b.vector,x);
	_cprintf("Test1\n");
	for (int i = 0; i < 5; i++)
		_cprintf("%6f\n",gsl_vector_get(x,i));
	
	gsl_vector * bb = gsl_vector_alloc(5);
	gsl_blas_dgemv(CblasNoTrans,1,&A.matrix,x,0,bb);
	_cprintf("\n");
	for (int j = 0; j < 5; j++)
		_cprintf("%6f\n",gsl_vector_get(bb,j));
}
//Test2
void GSL_SVD::OnBnClickedButton2()
{
	double a_data[] = { 2,4,
						3,-5,
						1,2 };
	gsl_matrix_view A = gsl_matrix_view_array(a_data, 3, 2);
	double b_data[] = { 11,3,6 };
	gsl_vector_view b = gsl_vector_view_array(b_data, 3);

	gsl_vector * x = gsl_vector_alloc(2);

	linearSolve_SVD(&A.matrix, &b.vector, x);
	//gsl_vector_fprintf(stdout,x,"%f");
	_cprintf("\nTest2\n");
	for (int i = 0; i < 2; i++)
	{
		_cprintf("%6f\n", gsl_vector_get(x, i));
	}

	gsl_vector * bb = gsl_vector_alloc(3);
	gsl_blas_dgemv(CblasNoTrans, 1, &A.matrix, x, 0, bb);

	for (int j = 0; j < 3; j++)
	{
		_cprintf("%6f\n", gsl_vector_get(bb, j));
	}
}

//test3
void GSL_SVD::OnBnClickedButton3()
{
	double a_data[] = {1,2,
					   2,4};
	gsl_matrix_view A = gsl_matrix_view_array(a_data,2,2);
	double b_data[] = {3,6};
	gsl_vector_view b = gsl_vector_view_array(b_data,2);

	gsl_vector * x = gsl_vector_alloc(2);
	_cprintf("\nTest3\n");
	linearSolve_SVD(&A.matrix,&b.vector,x);
	//gsl_vector_fprintf(stdout,x,"%6f");
	for (int i = 0; i < 2; i++)
		_cprintf("%6f\n",gsl_vector_get(x,i));

	gsl_vector *bb = gsl_vector_alloc(2);
	gsl_blas_dgemv(CblasNoTrans,1,&A.matrix,x,0,bb);

	//gsl_vector_fprintf(stdout, bb, "%6f");
	for (int j = 0; j < 2; j++)
		_cprintf("%6f\n",gsl_vector_get(bb,j));
}
//Test4
void GSL_SVD::OnBnClickedButton4()
{
	double a_data[] = { 1,2,
					    2,4 };
	gsl_matrix_view A = gsl_matrix_view_array(a_data,2,2);
	GSL_SVD svd;
	svd.SV_decomp(&A.matrix);
	_cprintf("\nTest4\n");
	puts("S=");
	gsl_vector * s = svd.getVectorS();
	for (int i = 0; i < 2; i++)
		_cprintf("%6f\n", gsl_vector_get(s, i));

	puts("\nV=");
	gsl_matrix * n = svd.getMatrixV();

	for (int j = 0; j < 2; j++)
		for(int k=0;k<2;k++)
		_cprintf("%6f\n", gsl_matrix_get(n, j,k));

	//double b_data[] = {3,6};
	//gsl_vector_view b = gsl_vector_view_array(b_data,2);
	//gsl_vector * x = gsl_vector_alloc(2);
	//svd.SV_solve(b, x);

	//puts("\nx=");
	//gsl_vector_fprintf(stdout,x,"%f");
}
