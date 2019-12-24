#pragma once


// CMethodDlg2 对话框

class CMethodDlg2 : public CDialog
{
	DECLARE_DYNAMIC(CMethodDlg2)

public:
	CMethodDlg2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMethodDlg2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
