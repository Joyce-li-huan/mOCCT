#include "stdafx.h"
#include"TemplateDlg.h"
#include "CMethodDlg.h"

IMPLEMENT_DYNAMIC(CMethodDlg,CDialog)

CMethodDlg::CMethodDlg(CWnd* pParent):TemplateDlg(CMethodDlg::IDD,pParent)//�̳�temp
{
}

void CMethodDlg::DoDataExchange(CDataExchange* pDX)
{
	TemplateDlg::DoDataExchange(pDX);//�̳�temp
}
BEGIN_MESSAGE_MAP(CMethodDlg,TemplateDlg)//�̳�temp��������Ϣ����
	ON_BN_CLICKED(IDOK, &CMethodDlg::OnBnClickedOk)//�Լ��Ļ���
END_MESSAGE_MAP()

void CMethodDlg::OnBnClickedOk()
{
	//���ø������еķ���
	TemplateDlg::HelloWorld();//this->HelloWorld();
}
// CMethodDlg ��Ϣ�������
void CMethodDlg::OnPaint()
{
	CRect rect;
	CPaintDC dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(0, 255, 255));   //����Ϊ��ɫ����   
	CDialog::OnPaint();
}

