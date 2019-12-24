#pragma once


// TNT_Test 对话框

class TNT_Test : public CDialog
{
	DECLARE_DYNAMIC(TNT_Test)

public:
	TNT_Test(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~TNT_Test();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TNT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
private:
//	Array2D<double> A;
	//Array2D<double> B(M,N);
	//Array2D<double> C(M,N)=0.0;
};
