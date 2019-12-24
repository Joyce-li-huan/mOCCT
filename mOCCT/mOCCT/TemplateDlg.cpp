// TemplateDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "mOCCT.h"
#include "TemplateDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// TemplateDlg 对话框

//IMPLEMENT_DYNAMIC(TemplateDlg, CDialog)

TemplateDlg::TemplateDlg(UINT nIDTemplate,CWnd* pParent /*=nullptr*/)
	: CDialog(nIDTemplate, pParent)
{

}

void TemplateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}
IMPLEMENT_DYNAMIC(TemplateDlg, CDialog)

BEGIN_MESSAGE_MAP(TemplateDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// TemplateDlg 消息处理程序

void TemplateDlg::OnPaint()
{
	CRect rect;
	CPaintDC dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect,RGB(0,255,0)); //设置为绿色背景   
CDialog:OnPaint();
}

void TemplateDlg::HelloWorld()
{
	AfxMessageBox(L"Hello World");
}