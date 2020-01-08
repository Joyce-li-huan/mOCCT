#pragma once
#include"resource.h"
#include "TemplateDlg.h"
class CMethodDlg :
	public TemplateDlg
{

	DECLARE_DYNAMIC(CMethodDlg)
public:
	//CMethodDlg(UINT nIDTemplate,CWnd* pParent=NULL);
	CMethodDlg(CWnd* pParent = NULL);
	enum { IDD = IDD_DIALOG2 };
	// 对话框数据
	//#ifdef AFX_DESIGN_TIME
		//enum { IDD = IDD_DIALOG2 };en
	//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
	//afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void On32839();
};

