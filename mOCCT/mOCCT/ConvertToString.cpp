// ConvertToString.cpp: 实现文件
//

#include "stdafx.h"
#include "mOCCT.h"
#include "ConvertToString.h"
#include "afxdialogex.h"


// ConvertToString 对话框

IMPLEMENT_DYNAMIC(ConvertToString, CDialog)

ConvertToString::ConvertToString(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG4, pParent)
{

}

ConvertToString::~ConvertToString()
{
}

void ConvertToString::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Rgb);
	DDX_Control(pDX, IDC_EDIT2, m_Unicode);
}


BEGIN_MESSAGE_MAP(ConvertToString, CDialog)
	ON_BN_CLICKED(IDOK, &ConvertToString::OnBnClickedOk)
END_MESSAGE_MAP()


// ConvertToString 消息处理程序
void ConvertToString::OnBnClickedOk()
{
	const char* str="线";
	char* Unicode=NULL;
	wchar_t* wstr = new wchar_t[20 / 2 + 1];
	memcpy(wstr, str, 20);
	int len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, Unicode, len, NULL, NULL);

	//char转换成CString
	int Len = MultiByteToWideChar(CP_ACP, 0, Unicode, 20, NULL, 0);
	TCHAR *buf = new TCHAR[Len+1];
	MultiByteToWideChar(CP_ACP,0,Unicode,20,buf,Len);
	buf[Len] = '/0';

	CString OutPut;
	OutPut.Append(buf);
	m_Unicode.SetWindowText(OutPut);
}
