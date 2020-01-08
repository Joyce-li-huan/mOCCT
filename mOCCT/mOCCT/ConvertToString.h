#pragma once


// ConvertToString 对话框

class ConvertToString : public CDialog
{
	DECLARE_DYNAMIC(ConvertToString)

public:
	ConvertToString(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ConvertToString();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString  UTF8AndUnicode_Convert(CString &strSource, UINT nSourceCodePage, UINT nTargetCodePage);

	CEdit m_Rgb;
	CEdit m_Unicode;
};
