﻿#pragma once


// listview 视图

class listview : public CListView
{
	DECLARE_DYNCREATE(listview)

protected:
	listview();           // 动态创建所使用的受保护的构造函数
	virtual ~listview();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


