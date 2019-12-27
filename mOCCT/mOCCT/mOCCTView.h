
// mOCCTView.h: CmOCCTView 类的接口
//

#pragma once



class CmOCCTView : public CView
{
protected: // 仅从序列化创建

	
	CmOCCTView() noexcept;
	DECLARE_DYNCREATE(CmOCCTView)

// 特性
public:
	CmOCCTDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	virtual void OnInitialUpdate();
// 实现
public:
	virtual ~CmOCCTView();

	//变量设置和图形显示设置
	Handle(V3d_View) myView;
	Standard_Integer               myXmin;
	Standard_Integer               myYmin;
	Standard_Integer               myXmax;
	Standard_Integer               myYmax;
	Handle(AIS_InteractiveContext) m_context;

	void FitAll()
	{
		if (!myView.IsNull()) myView->FitAll();  myView->ZFitAll();
	};

	TopoDS_Shape  MakeBottle(const Standard_Real myWidth, const Standard_Real myHeight,
		const Standard_Real myThickness);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawshepe();
	BOOL m_shepe;
	BOOL m_Zoom;
	BOOL m_Rota;
	BOOL m_Move;
	BOOL m_JBZoom;
	BOOL m_cylinder;
	BOOL m_box;
	BOOL m_cone;
	BOOL m_torus;
	BOOL m_light;
	BOOL m_line;
	BOOL m_wireframe;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnXyzXyz();
	afx_msg void On32778();
	afx_msg void On32779();
	afx_msg void On32780();
	afx_msg void On32781();

public:

	afx_msg void OnDraw32782();
	afx_msg void OnDraw32784();
	afx_msg void OnDraw32785();
	afx_msg void OnDraw32786();
	afx_msg void On32787();
	afx_msg void OnDrawLine();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void On32793();
	//gp_Pnt ChangeCoordinateSecond(double x,double y);
	gp_Vec NormalVector(TopoDS_Face F);
	afx_msg void OnDraw32820();
	afx_msg void OnGslSvd32824();
	afx_msg void OnGslTest();

	afx_msg void OnTntTest();
	afx_msg void OnMydllBasic();
	afx_msg void OnMydllCircle2d();
	afx_msg void On32829();

	afx_msg void On32830();

	afx_msg void On32834();
	afx_msg void On32835();
	afx_msg void On32836();
};

#ifndef _DEBUG  // mOCCTView.cpp 中的调试版本
inline CmOCCTDoc* CmOCCTView::GetDocument() const
   { return reinterpret_cast<CmOCCTDoc*>(m_pDocument); }
#endif

