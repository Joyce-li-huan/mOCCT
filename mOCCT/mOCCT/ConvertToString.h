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

//	char* EncodeToUTF8(const char* mbcsStr);

//	char* UTF8ToEncode(const char* mbcsStr);
};
//char* EncodeToUTF8(const char* mbcsStr)
//{
//	wchar_t*  wideStr;
//	char*   utf8Str;
//	int   charLen;
//
//	charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0);
//	wideStr = (wchar_t*)malloc(sizeof(wchar_t)*charLen);
//	MultiByteToWideChar(CP_ACP, 0, mbcsStr, -1, wideStr, charLen);
//
//	charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);
//
//	utf8Str = (char*)malloc(charLen);
//
//	WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);
//
//	free(wideStr);
//	return utf8Str;
//}
//char* UTF8ToEncode(const char* mbcsStr)
//{
//	wchar_t*  wideStr;
//	char*   unicodeStr;
//	int   charLen;
//
//
//	charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0);
//	wideStr = (wchar_t*)malloc(sizeof(wchar_t)*charLen);
//	MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, wideStr, charLen);
//
//
//	charLen = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);
//	unicodeStr = (char*)malloc(charLen);
//	WideCharToMultiByte(CP_ACP, 0, wideStr, -1, unicodeStr, charLen, NULL, NULL);
//
//
//	free(wideStr);
//	return unicodeStr;
//}