#pragma once


// TemplateDlg 对话框

class TemplateDlg : public CDialog
{
	DECLARE_DYNAMIC(TemplateDlg)

public:
	//TemplateDlg(CWnd* pParent = nullptr);   // 标准构造函数
	TemplateDlg(UINT nIDTemplate,CWnd* pParent= nullptr);
	//virtual ~TemplateDlg();

// 对话框数据
//#ifdef AFX_DESIGN_TIME
	//enum { IDD = IDD_DIALOG2 };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual afx_msg void OnPaint();
	void HelloWorld();
};
