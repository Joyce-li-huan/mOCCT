// TNT_Test.cpp: 实现文件
//

#include "stdafx.h"
#include "mOCCT.h"
#include "TNT_Test.h"
#include "afxdialogex.h"

#include<iostream>
#include"tnt.h"

#include<conio.h>
using namespace std;
using namespace TNT;

// TNT_Test 对话框

IMPLEMENT_DYNAMIC(TNT_Test, CDialog)

TNT_Test::TNT_Test(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DLG_TNT, pParent)
{

}

TNT_Test::~TNT_Test()
{
}

void TNT_Test::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TNT_Test, CDialog)
	ON_BN_CLICKED(IDOK, &TNT_Test::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &TNT_Test::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &TNT_Test::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &TNT_Test::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &TNT_Test::OnBnClickedButton3)
END_MESSAGE_MAP()


// TNT_Test 消息处理程序




void TNT_Test::OnBnClickedCancel()
{
	CDialog::OnCancel();
}
//test,Tnt_i_refvec.h
void TNT_Test::OnBnClickedOk()
{
	double arr[] = { 1,2,3,4 };
//	i_refvec<double> vec1, vec2(4), vec3(arr);//默认构造函数，产生一个空数组
//	_cprintf("Test  %f", vec3[2]);
}
//产生一个通常的矩阵类，没有采用计数
void TNT_Test::OnBnClickedButton1()
{
	Matrix<double>m1, m2(3, 4), m3(4,4,3);
	_cprintf("Test2 %f   %f  %f  ",m2.num_rows(),m2.num_cols(),m3);
}

//用于数学中的向量操作的载体，替换掉vector，且使用了引用计数
void TNT_Test::OnBnClickedButton2()
{
	double arr[] = {1,2,3,4};
	Array1D<double>vec1, vec2(4), vec3(4,arr);
//	_cprintf("Test3 %f  %f",vec3[2],vec3(3));
}

//example
void TNT_Test::OnBnClickedButton3()
{
	
	//Array2D <double> A(M,N,0,0);
}
