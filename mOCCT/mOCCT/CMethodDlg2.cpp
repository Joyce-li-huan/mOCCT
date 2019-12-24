// CMethodDlg2.cpp: 实现文件
//

#include "stdafx.h"
#include "mOCCT.h"
#include "CMethodDlg2.h"
#include "afxdialogex.h"


// CMethodDlg2 对话框

IMPLEMENT_DYNAMIC(CMethodDlg2, CDialog)

CMethodDlg2::CMethodDlg2(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG3, pParent)
{

}

CMethodDlg2::~CMethodDlg2()
{
}

void CMethodDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMethodDlg2, CDialog)
	ON_BN_CLICKED(IDOK, &CMethodDlg2::OnBnClickedOk)
END_MESSAGE_MAP()


// CMethodDlg2 消息处理程序


void CMethodDlg2::OnBnClickedOk()
{
	AfxMessageBox(L"Hello World");
}
