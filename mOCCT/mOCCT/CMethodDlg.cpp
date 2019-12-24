#include "stdafx.h"
#include"TemplateDlg.h"
#include "CMethodDlg.h"

IMPLEMENT_DYNAMIC(CMethodDlg,CDialog)

CMethodDlg::CMethodDlg(CWnd* pParent):TemplateDlg(CMethodDlg::IDD,pParent)//继承temp
{
}

void CMethodDlg::DoDataExchange(CDataExchange* pDX)
{
	TemplateDlg::DoDataExchange(pDX);//继承temp
}
BEGIN_MESSAGE_MAP(CMethodDlg,TemplateDlg)//继承temp的所有消息机制
	ON_BN_CLICKED(IDOK, &CMethodDlg::OnBnClickedOk)//自己的机制
END_MESSAGE_MAP()

void CMethodDlg::OnBnClickedOk()
{
	//调用父窗口中的方法
	TemplateDlg::HelloWorld();//this->HelloWorld();
}
// CMethodDlg 消息处理程序
void CMethodDlg::OnPaint()
{
	CRect rect;
	CPaintDC dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(0, 255, 255));   //设置为蓝色背景   
	CDialog::OnPaint();
}

