
// mOCCTDoc.h: CmOCCTDoc 类的接口
//


#pragma once
#include"ColoredShapes.h"
#include"AIS_InteractiveContext.hxx"

class CmOCCTDoc : public CDocument
{
protected: // 仅从序列化创建
	CmOCCTDoc() noexcept;
	DECLARE_DYNCREATE(CmOCCTDoc)

// 特性
public:
	void Put3DOnTop(bool isMax = true);
	Handle(AIS_InteractiveContext) myAISContext;
	Handle(V3d_Viewer) myViewer;
	Handle(V3d_Viewer) GetViewer(void) { return myViewer; }

	Handle(V3d_View) m_3dView;

	virtual void DragEvent(const Standard_Integer theMouseX,
							const Standard_Integer theMouseY,
							const Standard_Integer theState,
							const Handle(V3d_View)& theView);
	virtual void InputEvent(const Standard_Integer theMouseX,
		const Standard_Integer theMouseY,
		const Handle(V3d_View)& theView);

	Handle(AIS_InteractiveContext)& GetISessionContext() { return myAISContext2D; };


// 操作
public:
	Handle(TDocStd_Document) GetOcafDoc() { return myDoc; };
private:
	Handle(AIS_Trihedron) myTrihedron;
	Handle(BRepPrim_Cylinder) myCylinder;

	Handle(BRepPrim_Sphere) mySphere;
	Handle(AIS_Shape) mySphere1;

	Handle(TDocStd_Document) myDoc;

	//显示点
	Handle(AIS_InteractiveContext) myAISContext2D;

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//在DOC中定义三个IGES函数
	void ReadIGES(const Handle(AIS_InteractiveContext)& anInteractiveContext);
	void Fit();
	Handle(TopTools_HSequenceOfShape) CmOCCTDoc::ReadIGES();

	Standard_Integer CmOCCTDoc::ReadIGES(const Standard_CString& aFileName,
		Handle(TopTools_HSequenceOfShape)& aHSequenceOfShape);
	
	Standard_EXPORT AIS_StatusOfDetection MoveTo(const Standard_Integer thXPix,
												const Standard_Integer  theYPix,
												const Handle(V3d_View)& theView,
												const Standard_Boolean  theToRedrawOnUpdate);

	Handle(AIS_InteractiveContext)& GetAISContext() { return myAISContext; }



#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CmOCCTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	CColoredShapes* m_pcoloredshapeList;
	
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	int Current;
	void DrawSphere();
	afx_msg void OnImportIges();

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

	afx_msg void OnXyzXyz();
	afx_msg void OnDrawRac();
	void make_cylinder(Standard_Real _R,Standard_Real _H);
	void MakeCone();
	void Drawtorus();
	void DrawPane();
	void DrawPoint();
	void OnLine();
	afx_msg void OnDrawBox();
	virtual void MoveEvent(const Standard_Integer theMouseX,
		const Standard_Integer theMouseY,
		const Handle(V3d_View)& theView);
	afx_msg void On32790();
	afx_msg void On32791();
	afx_msg void On32792();
	void Wirefrane();


	afx_msg void OnUpdate32793(CCmdUI *pCmdUI);
	afx_msg void OnUpdate32797(CCmdUI *pCmdUI);
	afx_msg void OnUpdate32798(CCmdUI *pCmdUI);
	afx_msg void On32797();
	
	afx_msg void OnDrawPoint();
	afx_msg void On32802();
	afx_msg void On32811();
	afx_msg void On32812();
	afx_msg void On32803();
	afx_msg void On32813();
	afx_msg void On32814();
	afx_msg void OnDraw32820();
	afx_msg void OnDraw32818();
	afx_msg void OnDraw32816();
	afx_msg void OnDraw32815();
	afx_msg void OnDraw32817();
	afx_msg void OnDraw32819();
	afx_msg void On32830();
	afx_msg void On32831();
	afx_msg void On32832();
	afx_msg void On32833();
	afx_msg void On32834();
	afx_msg void On32837();
};
