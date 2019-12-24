// listview.cpp: 实现文件
//

#include "stdafx.h"
#include "mOCCT.h"
#include "listview.h"


// listview

IMPLEMENT_DYNCREATE(listview, CListView)

listview::listview()
{

}

listview::~listview()
{
}

BEGIN_MESSAGE_MAP(listview, CListView)
END_MESSAGE_MAP()


// listview 诊断

#ifdef _DEBUG
void listview::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void listview::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// listview 消息处理程序
