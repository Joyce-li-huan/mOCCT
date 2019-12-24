
// mOCCTDoc.cpp: CmOCCTDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "mOCCT.h"
#endif

#include "mOCCTDoc.h"
#include <Geom_Line.hxx>
#include <propkey.h>
#include"mOCCTView.h"
#include"MainFrm.h"
#include"GeoSource.h"
#include <StdPrs_Point.hxx>

#include"CMethodDlg.h"
#include"CMethodDlg2.h"
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif

// CmOCCTDoc

IMPLEMENT_DYNCREATE(CmOCCTDoc, CDocument)

BEGIN_MESSAGE_MAP(CmOCCTDoc, CDocument)
	ON_COMMAND(ID_IMPORT_IGES, &CmOCCTDoc::OnImportIges)
	ON_COMMAND(ID_XYZ_XYZ, &CmOCCTDoc::OnXyzXyz)
	ON_COMMAND(ID_DRAW_RAC, &CmOCCTDoc::OnDrawRac)
	ON_COMMAND(ID_32790, &CmOCCTDoc::On32790)
	ON_COMMAND(ID_32791, &CmOCCTDoc::On32791)
	ON_COMMAND(ID_32792, &CmOCCTDoc::On32792)
	
	ON_UPDATE_COMMAND_UI(ID_32793, &CmOCCTDoc::OnUpdate32793)
	ON_UPDATE_COMMAND_UI(ID_32797, &CmOCCTDoc::OnUpdate32797)
	ON_UPDATE_COMMAND_UI(ID_32798, &CmOCCTDoc::OnUpdate32798)
	ON_COMMAND(ID_32797, &CmOCCTDoc::On32797)

	ON_COMMAND(ID_DRAW_POINT, &CmOCCTDoc::OnDrawPoint)
	ON_COMMAND(ID_32802, &CmOCCTDoc::On32802)
	ON_COMMAND(ID_32811, &CmOCCTDoc::On32811)
	ON_COMMAND(ID_32812, &CmOCCTDoc::On32812)
	ON_COMMAND(ID_32803, &CmOCCTDoc::On32803)
	ON_COMMAND(ID_32813, &CmOCCTDoc::On32813)
	ON_COMMAND(ID_32814, &CmOCCTDoc::On32814)
	ON_COMMAND(ID_DRAW_32820, &CmOCCTDoc::OnDraw32820)
	ON_COMMAND(ID_DRAW_32818, &CmOCCTDoc::OnDraw32818)
	ON_COMMAND(ID_DRAW_32816, &CmOCCTDoc::OnDraw32816)
	ON_COMMAND(ID_DRAW_32815, &CmOCCTDoc::OnDraw32815)
	ON_COMMAND(ID_DRAW_32817, &CmOCCTDoc::OnDraw32817)
	ON_COMMAND(ID_DRAW_32819, &CmOCCTDoc::OnDraw32819)
	ON_COMMAND(ID_32830, &CmOCCTDoc::On32830)
	ON_COMMAND(ID_32831, &CmOCCTDoc::On32831)
	ON_COMMAND(ID_32832, &CmOCCTDoc::On32832)
	ON_COMMAND(ID_32833, &CmOCCTDoc::On32833)
END_MESSAGE_MAP()


// CmOCCTDoc 构造/析构

CmOCCTDoc::CmOCCTDoc() noexcept
{
	// TODO: 在此添加一次性构造代码
	//添加间接设备环境和图形接口

	Handle(Graphic3d_GraphicDriver) theGraphicDriver = ((CmOCCTApp*)AfxGetApp())->GetGraphicDriver();

	myViewer = new V3d_Viewer(theGraphicDriver);
	myViewer->SetDefaultLights();
	myViewer->SetLightOn();

	myAISContext = new AIS_InteractiveContext(myViewer);

	myAISContext->SetDisplayMode(AIS_Shaded, Standard_False);
	myAISContext->SetAutomaticHilight(Standard_False);
	


	//if (m_pcoloredshapeList) delete m_pcoloredshapeList;
	m_pcoloredshapeList = new CColoredShapes();
}

CmOCCTDoc::~CmOCCTDoc()
{
	if (m_pcoloredshapeList)
	{
		delete m_pcoloredshapeList;
		//m_pcoloredshapeList= nullptr;

	}
}

BOOL CmOCCTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	//TPrsStd_AISViewer::New(myDoc->Main(), myViewer);
	return TRUE;
}

// CmOCCTDoc 序列化
void CmOCCTDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		ar << m_pcoloredshapeList;
	}
	else
	{
		// TODO: 在此添加加载代码
		ar >> m_pcoloredshapeList;
		m_pcoloredshapeList->Display(myAISContext);
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CmOCCTDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CmOCCTDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CmOCCTDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CmOCCTDoc 诊断

#ifdef _DEBUG
void CmOCCTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CmOCCTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CmOCCTDoc 命令
void CmOCCTDoc::OnImportIges()
{
	// TODO: 在此添加命令处理程序代码
	Handle(TopTools_HSequenceOfShape) aSeqOfShape = CmOCCTDoc::ReadIGES();
	for (int i = 1; i <= aSeqOfShape->Length(); i++)
	{
		m_pcoloredshapeList->Add(Quantity_NOC_YELLOW, aSeqOfShape->Value(i));
		m_pcoloredshapeList->Display(myAISContext);
	}
	Fit();
}

void CmOCCTDoc::ReadIGES(const Handle(AIS_InteractiveContext)& anInteractiveContext)
{
	Handle(TopTools_HSequenceOfShape)aSequence = CmOCCTDoc::ReadIGES();
	for (int i = 1; i <= aSequence->Length(); i++)
		anInteractiveContext->Display(new AIS_Shape(aSequence->Value(i)),Standard_False);
	anInteractiveContext->UpdateCurrentViewer();
	anInteractiveContext->IsoNumber();
}
Handle(TopTools_HSequenceOfShape) CmOCCTDoc::ReadIGES()
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"IGES Files (*.iges , *.igs)|*.iges; *.igs|All Files (*.*)|*.*||",NULL);
	CString SHAREPATHValue;
	SHAREPATHValue.GetEnvironmentVariable(L"CSF_OCCTDataPath");
	CString initdir = (SHAREPATHValue + "\\iges");

	dlg.m_ofn.lpstrInitialDir = initdir;
	Handle(TopTools_HSequenceOfShape) aSequence = new TopTools_HSequenceOfShape();

	if (dlg.DoModal() == IDOK)

	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
	
		TCollection_AsciiString aFileName((const wchar_t*)dlg.GetPathName());
		Standard_Integer status = ReadIGES(aFileName.ToCString(), aSequence);
		if (status != IFSelect_RetDone)
		{
			MessageBox(NULL,_T("Error : The file is not read"), _T("CasCade Error"), MB_ICONERROR);
		}
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	}
	return aSequence;
	
}
Standard_Integer CmOCCTDoc::ReadIGES(const Standard_CString& aFileName,Handle(TopTools_HSequenceOfShape)& aHSequenceOfShape)
{
	IGESControl_Reader Reader;
	Standard_Integer status = Reader.ReadFile(aFileName);
	if (status != IFSelect_RetDone) return status;
	Reader.TransferRoots();
	TopoDS_Shape aShape = Reader.OneShape();
	aHSequenceOfShape->Append(aShape);
	return status;
}
void CmOCCTDoc::Fit()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CmOCCTView *pView = (CmOCCTView *)pFrame->GetActiveView();
	pView->FitAll();

}

void CmOCCTDoc::OnXyzXyz()
{

}
//坐标
void CmOCCTDoc::OnDrawRac()
{
	// TODO: 在此添加命令处理程序代码
		// TODO: 在此添加命令处理程序代码
	if (myAISContext->IsDisplayed(myTrihedron))
	{
		myAISContext->Remove(myTrihedron, Standard_True);
	}
	else
	{
		Handle(Geom_Axis2Placement) myTrihedronAxis = new Geom_Axis2Placement(gp::XOY());
		myTrihedron = new AIS_Trihedron(myTrihedronAxis);
		myAISContext->SetTrihedronSize(200, Standard_False);
		myAISContext->Display(myTrihedron, Standard_True);



	



	}
}

//球
void CmOCCTDoc::DrawSphere()
{
	// TODO: 在此处添加实现代码.
	//gp_Ax2 anAx2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., -1.));
	//Handle(Geom_Circle) aGeomCircle = new Geom_Circle(anAx2, 300);

	BRepPrimAPI_MakeSphere mkSphere(gp_Pnt(0,0,0),100.);
	TopoDS_Shape Sphere = mkSphere.Shape();
	Handle(AIS_Shape) myAISSphere = new AIS_Shape(Sphere);
	myAISContext->Display(myAISSphere, Standard_False);

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild = (CMDIChildWnd *)pFrame->GetActiveFrame();
	CmOCCTView *pView = (CmOCCTView *)pChild->GetActiveView();
	pView->FitAll();
}

//圆柱
void CmOCCTDoc::make_cylinder(Standard_Real _R, Standard_Real _H)
{
	// TODO: 在此处添加实现代码.
	TopoDS_Shape t_topo_cylinder = BRepPrimAPI_MakeCylinder(_R,_H).Shape();
	Handle(AIS_Shape) t_ais_cylinder = new AIS_Shape(t_topo_cylinder);
	myAISContext->Display(t_ais_cylinder,Standard_True);

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild = (CMDIChildWnd *)pFrame->GetActiveFrame();
	CmOCCTView *pView = (CmOCCTView *)pChild->GetActiveView();
	pView->FitAll();
}

//正方形
void CmOCCTDoc::OnDrawBox()
{
	// TODO: 在此添加命令处理程序代码
	BRepPrimAPI_MakeBox B(gp_Pnt(0, 0, 0), 100.,100.,100.);//坐标轴，长宽高
	TopoDS_Shape t_topo_box = B.Shape();
	Handle(AIS_Shape) t_ais_box = new AIS_Shape(t_topo_box);
	myAISContext->Display(t_ais_box,Standard_True);

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild = (CMDIChildWnd *)pFrame->GetActiveFrame();
	CmOCCTView *pView = (CmOCCTView *)pChild->GetActiveView();
	pView->FitAll();
}

//圆锥
void CmOCCTDoc::MakeCone()
{
	//BRepPrimAPI_MakeCone C((1,0,2),200.,150.,100.);//R1 & R2 & H,坐标
	BRepPrimAPI_MakeCone C(1.0, 0.0, 2.0);//R1 & R2 & H,坐标
	TopoDS_Shape t_topo_cone = C.Shape();
	Handle(AIS_Shape) t_ais_cone = new AIS_Shape(t_topo_cone);
	myAISContext->Display(t_ais_cone,Standard_True);

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild = (CMDIChildWnd *)pFrame->GetActiveFrame();
	CmOCCTView *pView = (CmOCCTView *)pChild->GetActiveView();
	pView->FitAll();
}
//圆环
void CmOCCTDoc::Drawtorus()
{
	BRepPrimAPI_MakeTorus Torus(2, 0.5);
	TopoDS_Shape t_topo_torus = Torus.Shape();
	Handle(AIS_Shape) t_ais_torus = new AIS_Shape(t_topo_torus);
	myAISContext->Display(t_ais_torus,Standard_True);
	myAISContext->Display(t_ais_torus,Standard_True);

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild = (CMDIChildWnd *)pFrame->GetActiveFrame();
	CmOCCTView *pView = (CmOCCTView *)pChild->GetActiveView();
	pView->FitAll();
}
//高亮
void CmOCCTDoc::MoveEvent(const Standard_Integer theMouseX,
							const Standard_Integer theMouseY,
							const Handle(V3d_View)& theView)
{
	myAISContext->MoveTo(theMouseX, theMouseY, theView, Standard_True);
}
//线
void CmOCCTDoc::OnLine()
{
	gp_Lin aGpLin(gp_Pnt(0.,0.,0.),gp_Dir(0.,1.,0.));//gp_Dir:1代表线的方向,XYZ
	Handle(Geom_Line) aGeomLin = new Geom_Line(aGpLin);
	Handle(AIS_Line) anAISLine = new AIS_Line(aGeomLin);
	myAISContext->Display(anAISLine,Standard_True);
	
}
//点
void CmOCCTDoc::DrawPoint()
{
}
//平面
void CmOCCTDoc::DrawPane()
{
	gp_Pln aClipPlane(gp_Pnt(0.0,0.0,0.0),gp_Dir(1.0,0.0,0.0));//确定基面方向
	gp_Pln aFacePlane(gp_Pnt(1.0, 0.0, 0.0),gp_Dir(1.0,0.0,0.0));//面和面方向
	//gp_Pln p1(gp_Pnt(0.0,0.0,0.0));//点1
//	gp_Pnt p2();//点2
//	gp_Pnt p3();//点3

	//创建剪切面到视图中
	Handle(Graphic3d_ClipPlane) myClippingPlane = new Graphic3d_ClipPlane(aClipPlane);
//	BRepBuilderAPI_MakeFace;
	
}
//隐藏
void CmOCCTDoc::On32790()
{
	// TODO: 在此添加命令处理程序代码
	myAISContext->EraseSelected(Standard_True);

}

//选中物体隐藏
void CmOCCTDoc::DragEvent(const Standard_Integer theMouseX,
							const Standard_Integer theMouseY,
							const Standard_Integer theState,
							const Handle(V3d_View)& theView)
{
	static Standard_Integer aStartDragX = 0;
	static Standard_Integer aStartDragY = 0;
	switch (theState)
	{
		case -1:
		{
			aStartDragX = theMouseX;
			aStartDragY = theMouseY;
			break;
		}
		case 0:
		{
			myAISContext->UpdateCurrentViewer();
			break;
		}
		case 1:
		{
			myAISContext->Select(aStartDragX, aStartDragY,
				theMouseX, theMouseY,
				theView, Standard_True);
			break;
		}
	}
}
//选中物体隐藏
void CmOCCTDoc::InputEvent(const Standard_Integer theMouseX,
	const Standard_Integer theMouseY,
	const Handle(V3d_View)& theView)
{
	myAISContext->MoveTo(theMouseX, theMouseY, theView, Standard_False);
	myAISContext->Select(Standard_True);
}
//显示隐藏物体
void CmOCCTDoc::On32791()
{
	// TODO: 在此添加命令处理程序代码
	myAISContext->DisplayAll(Standard_True);
}
//移除物体
void CmOCCTDoc::On32792()
{
	// TODO: 在此添加命令处理程序代码
	for (myAISContext->InitSelected(); myAISContext->MoreSelected(); myAISContext->InitSelected())
		myAISContext->Remove(myAISContext->SelectedInteractive(), Standard_True);
}
//让透明按钮可见
void CmOCCTDoc::OnUpdate32793(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	bool OneOrMoreInShadingOrColoredMesh = false;
	for (myAISContext->InitSelected(); myAISContext->MoreSelected(); myAISContext->NextSelected())
		if (myAISContext->IsDisplayed(myAISContext->SelectedInteractive(), 1) || myAISContext->IsDisplayed(myAISContext->SelectedInteractive(), 6))
			OneOrMoreInShadingOrColoredMesh = true;
	pCmdUI->Enable(OneOrMoreInShadingOrColoredMesh);
}

////后退按钮不可用
void CmOCCTDoc::OnUpdate32797(CCmdUI *pCmdUI)
{
//	if (myDoc->GetAvailableRedos() > 0) pCmdUI->Enable(Standard_True);
//	else pCmdUI->Enable(Standard_False);
}
//前进响应事件
void CmOCCTDoc::On32797()
{
	//myDoc->Undo();
	//myDoc->CommitCommand();
	//myAISContext->UpdateCurrentViewer();

	//UpdateAllViews(NULL);

}
////前进按钮变灰不可用
void CmOCCTDoc::OnUpdate32798(CCmdUI *pCmdUI)
{
//	if (myDoc->GetAvailableUndos() > 0) pCmdUI->Enable(Standard_True);
//	else pCmdUI->Enable(Standard_False);
}
//点
void CmOCCTDoc::OnDrawPoint()
{
	// TODO: 在此添加命令处理程序代码
	gp_Pnt p1(1,2,3);
	Handle(Geom_CartesianPoint) aGeomPoint = new Geom_CartesianPoint(p1);
	Handle(AIS_Point) Point = new AIS_Point(aGeomPoint);
	myAISContext->Display(Point,Standard_True);

}	
//点
void CmOCCTDoc::On32802()
{
	// TODO: 在此添加命令处理程序代码
	Current = 1;
	GeoSource::gpTest1(this);
	myViewer->Update();
	
}
void CmOCCTDoc::Put3DOnTop(bool isMax)
{
	POSITION position = GetFirstViewPosition();
	while (position!=(POSITION)NULL)
	{
		CView* pCurrentView = (CView*)GetNextView(position);
		if (pCurrentView->IsKindOf(RUNTIME_CLASS(CmOCCTView)))
		{
			ASSERT_VALID(pCurrentView);
			CFrameWnd* pParentFrm = pCurrentView->GetParentFrame();
			ASSERT(pParentFrm != (CFrameWnd *)NULL);
			// simply make the frame window visible
			if (isMax)
			{
				pParentFrm->ActivateFrame(SW_SHOWMAXIMIZED);
			}
			else
			{
				pParentFrm->ActivateFrame(SW_SHOW);
			}
		}
	}

}

void CmOCCTDoc::On32811()
{
	// TODO: 在此添加命令处理程序代码
	GeoSource::gpTest2(this);
}
//3D点，显示点不显示坐标即标注说明
void CmOCCTDoc::On32812()
{
	gp_Pnt p1(110, 60, 100);
	Handle(AIS_Point) aRect1 = new AIS_Point(new Geom_CartesianPoint(p1)); 
	myAISContext->SetColor(aRect1, Quantity_NOC_BLUE3,this);
	myAISContext->Display(aRect1, true);

}

//3D线
void CmOCCTDoc::On32803()
{
	TopoDS_Edge E14 = BRepBuilderAPI_MakeEdge(gp_Pnt(0.0,68.0,0.),gp_Pnt(40.,0.,0.));
		Handle_AIS_Shape aRect1 = new AIS_Shape(E14);
		myAISContext->Display(aRect1,true);
		myAISContext->SetColor(aRect1, Quantity_NOC_YELLOW,this);
}

//3D面
void CmOCCTDoc::On32813()
{
	TopoDS_Face BlueFace;// BrownFace; 
	TopoDS_Edge E11 = BRepBuilderAPI_MakeEdge(gp_Pnt(40., 0., 0.), gp_Pnt(82.5, 25., 0.)); 
	TopoDS_Edge E12 = BRepBuilderAPI_MakeEdge(gp_Pnt(82.5, 25., 0.), gp_Pnt(42.5, 93., 0.)); 
	TopoDS_Edge E13 = BRepBuilderAPI_MakeEdge(gp_Pnt(42.5, 93., 0.), gp_Pnt(0., 68., 0.)); 
	TopoDS_Edge E14 = BRepBuilderAPI_MakeEdge(gp_Pnt(0., 68., 0.), gp_Pnt(40., 0., 0.));
	BRepBuilderAPI_MakeWire W1(E11, E12, E13, E14);  
	BlueFace = BRepBuilderAPI_MakeFace(W1); 
	Handle(AIS_Shape) Blue = new AIS_Shape(BlueFace);
	myAISContext->SetColor(Blue,Quantity_NOC_WHITE, Standard_False); 
	myAISContext->SetMaterial(Blue, Graphic3d_NOM_PLASTIC, Standard_False);   

	myAISContext->Display(Blue, Standard_True);

}

//3D线框，由组合线段构成线框
void CmOCCTDoc::On32814()
{
	TopoDS_Face BlueFace, BrownFace; 
	TopoDS_Edge E11 = BRepBuilderAPI_MakeEdge(gp_Pnt(40., 0., 0.), gp_Pnt(82.5, 25., 0.));
	TopoDS_Edge E12 = BRepBuilderAPI_MakeEdge(gp_Pnt(82.5, 25., 0.), gp_Pnt(42.5, 93., 0.));
	TopoDS_Edge E13 = BRepBuilderAPI_MakeEdge(gp_Pnt(42.5, 93., 0.), gp_Pnt(0., 68., 0.)); 
	TopoDS_Edge E14 = BRepBuilderAPI_MakeEdge(gp_Pnt(0., 68., 0.), gp_Pnt(40., 0., 0.)); 
	BRepBuilderAPI_MakeWire W1(E11, E12, E13, E14); 

	//TopoDS_Shape s = BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(W1),gp_Vec(0,0,50));//拉伸
	//Handle(AIS_Shape) ais1 = new AIS_Shape(s);
	//myAISContext->SetColor(ais1, Quantity_NOC_WHITE, Standard_False);
	//myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);
	//myAISContext->Display(ais1, Standard_True);

	Handle(AIS_Shape) Blue = new AIS_Shape(W1.Wire()); 
	myAISContext->SetColor(Blue, Quantity_NOC_WHITE, Standard_False);
	myAISContext->SetMaterial(Blue, Graphic3d_NOM_PLASTIC, Standard_False);    
	myAISContext->Display(Blue, Standard_True);

}

//圆
void CmOCCTDoc::OnDraw32820()
{
	gp_Circ circle(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 180);
	Handle(Geom_Circle) circle1 = new Geom_Circle(circle);
	Handle(AIS_Circle) CR = new AIS_Circle(circle1);
	myAISContext->Display(CR,Standard_True);
	
}
//椭圆
void CmOCCTDoc::OnDraw32818()
{
	gp_Elips Elips(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(1,1,1)),530, 230);
	Handle(Geom_Ellipse) Elips1 = new Geom_Ellipse(Elips);
	TopoDS_Edge EE = BRepBuilderAPI_MakeEdge(Elips1);
	Handle_AIS_Shape EP = new AIS_Shape(EE);
	myAISContext->Display(EP, true);

	//椭圆体
	//RedEdge = BRepBuilderAPI_MakeEdge(Elips,0,2*M_PI);
	//TopoDS_Shape S = BRepPrimAPI_MakeRevol(RedEdge,gp_Ax1(gp_Pnt(0.001,0,0),gp_Dir(0,1,0)));
	//Handle(AIS_Shape) ais4 = new AIS_Shape(S); 
	//myAISContext->SetColor(ais4, Quantity_NOC_BLUE3,Standard_True); 
	//myAISContext->SetMaterial(ais4, Graphic3d_NOM_PLASTIC,Standard_True);   
	//myAISContext->Display(ais4,Standard_True);
}

//管形
void CmOCCTDoc::OnDraw32816()
{
	TColgp_Array1OfPnt CurvePoles(1, 4);
	gp_Pnt pt = gp_Pnt(0., 0., 0.);
	CurvePoles(1) = pt; 
	pt = gp_Pnt(20., 50., 0.);
	CurvePoles(2) = pt; 
	pt = gp_Pnt(60., 100., 0.);
	CurvePoles(3) = pt;
	pt = gp_Pnt(150., 0., 0.);
	CurvePoles(4) = pt; 
	Handle(Geom_BezierCurve) curve = new Geom_BezierCurve(CurvePoles);
	TopoDS_Edge E = BRepBuilderAPI_MakeEdge(curve); 
	TopoDS_Wire W = BRepBuilderAPI_MakeWire(E);
	Handle(AIS_Shape) ais1 = new AIS_Shape(W);
	myAISContext->Display(ais1, Standard_False);
	Fit(); 
	Sleep(500); 
	gp_Circ c = gp_Circ(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 1., 0.)), 10.);
	TopoDS_Edge Ec = BRepBuilderAPI_MakeEdge(c); 
	TopoDS_Wire Wc = BRepBuilderAPI_MakeWire(Ec);
	Handle(AIS_Shape) ais3 = new AIS_Shape(Wc); 
	myAISContext->Display(ais3, Standard_False); 
	TopoDS_Face F = BRepBuilderAPI_MakeFace(gp_Pln(gp::ZOX()), Wc);
	TopoDS_Shape S = BRepOffsetAPI_MakePipe(W, F); 
	Handle(AIS_Shape) ais2 = new AIS_Shape(S); 
	myAISContext->SetColor(ais2, Quantity_NOC_MATRABLUE, Standard_False);
	myAISContext->SetMaterial(ais2, Graphic3d_NOM_PLASTIC, Standard_False);  
	myAISContext->Display(ais2, Standard_False);


}
//矢量点
void CmOCCTDoc::OnDraw32815()
{
	gp_Pnt P(0,0,0);
	gp_Dir D(0,0,1);
	//gp_Ax3 A(P,D);
	//gp_Dir AX = A.XDirection();
	Handle(Prs3d_LineAspect) anAxesAspect = new Prs3d_LineAspect(Quantity_NOC_RED, Aspect_TOL_SOLID, 1.0);
	Handle(ISession_Direction) aDirection2 = new ISession_Direction(P, D, 5);
	aDirection2->SetLineAspect(anAxesAspect);
	myAISContext->Display(aDirection2,Standard_False);
}
//圆形槽
void CmOCCTDoc::OnDraw32817()
{
	//gp_Circ
}

//矩形槽
void CmOCCTDoc::OnDraw32819()
{
	TopoDS_Shape S = BRepPrimAPI_MakeBox(gp_Ax2(gp_Pnt(0,0,0), gp_Dir(0, 0, 1)),500,500,0).Shape();
	Handle(AIS_Shape) ais1 = new AIS_Shape(S);
	myAISContext->SetColor(ais1, Quantity_NOC_WHITE, Standard_False); 
	myAISContext->SetMaterial(ais1, Graphic3d_NOM_PLASTIC, Standard_False);   
	myAISContext->Display(ais1,Standard_False);
	Fit();

	//拉伸成矩形体
	//BRepBuilderAPI_MakeWire mkw;
	//TopoDS_Edge E11 = BRepBuilderAPI_MakeEdge(gp_Pnt(40., 0., 0.), gp_Pnt(82.5, 25., 0.));
	//TopoDS_Edge E12 = BRepBuilderAPI_MakeEdge(gp_Pnt(82.5, 25., 0.), gp_Pnt(42.5, 93., 0.));	
	//TopoDS_Edge E13 = BRepBuilderAPI_MakeEdge(gp_Pnt(42.5, 93., 0.), gp_Pnt(0., 68., 0.));
	//TopoDS_Edge E14 = BRepBuilderAPI_MakeEdge(gp_Pnt(0., 68., 0.), gp_Pnt(40., 0., 0.));
	//TopoDS_Wire W1 = BRepBuilderAPI_MakeWire(E11, E12, E13, E14); 
	////TopoDS_Shape S = BRepPrimAPI_MakePrism(W1,gp_Vec(0.,0.,50));                     //线框TopoDS_Wire在指定向量拉伸	
	////TopoDS_Shape S = BRepPrimAPI_MakePrism(E14,gp_Vec(0.,0.,50));						//边TopoDS_Edge在指定向量拉伸	
	//TopoDS_Shape S =BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(W1),gp_Vec(0.,0.,50));  //面TopoDS_Face在指定向量拉伸	
	//Handle(AIS_Shape) ais1 = new AIS_Shape(S);     
	//myAISContext->SetColor(ais1,Quantity_NOC_CYAN2,Standard_False); 
	//myAISContext->SetMaterial(ais1,Graphic3d_NOM_PLASTIC,Standard_False);   
	//myAISContext->Display(ais1,Standard_False);
	//myAISContext->SetCurrentObject(ais1,Standard_False);
	//Fit();	
	
	
	//矩形+孔+矩形槽：
	//TopoDS_Shape S1 = BRepPrimAPI_MakeBox(gp_Pnt(0., 0., 0.), 500., 500., 500).Shape();//大矩形
	//Handle(AIS_Shape) ais1 = new AIS_Shape(S1); 
	//myAISContext->SetColor(ais1,Quantity_NOC_WHITE,Standard_False);
	//myAISContext->SetMaterial(ais1,Graphic3d_NOM_PLASTIC,Standard_False);    
	//myAISContext->Display(ais1,Standard_False);  

	//TopoDS_Shape S2 = BRepPrimAPI_MakeBox(gp_Pnt(-0.01,200,-0.01),100,100,50).Shape();//小矩 
	//Handle(AIS_Shape) ais2 = new AIS_Shape(S2);
	//myAISContext->SetColor(ais2,Quantity_NOC_YELLOW,Standard_False);
	//myAISContext->SetMaterial(ais2,Graphic3d_NOM_PLASTIC,Standard_False);   
	//myAISContext->Display(ais2,Standard_False);   
	/*int num=100; 
	TopoDS_Shape S3; 
	for (int i = 0; i < 7; i++)
	{
		S3 = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(100., -0.01, num), gp_Dir(0., 1., 0.)), 10., 110., 360.*M_PI / 180).Shape();
		Handle(AIS_Shape) ais3 = new AIS_Shape(S3); myAISContext->SetColor(ais3, Quantity_NOC_BLUE3, Standard_False);
		myAISContext->SetMaterial(ais3, Graphic3d_NOM_PLASTIC, Standard_False);
		myAISContext->Display(ais3, Standard_False);
		num += 50;
	}
*/
}

//显示测试头坐标点
void CmOCCTDoc::On32830()
{
	int aWidth, aHeight;
	m_3dView->Window()->Size(aWidth,aHeight);
	
	myViewer->Redraw();

	//Handle(AIS_InteractiveContext) theContext;
	//Handle(AIS_InteractiveObject) theInterObj;
	//Standard_Integer andId = 3;
	//myViewer->AddZLayer(andId);
	//theContext->SetZLayer(theInterObj,andId);

	//Graphic3d_ZLayerSettings aSettings=myViewer->ZLayerSettings(andId);
	//aSettings.SetEnableDepthTest(true);
	//aSettings.SetEnableDepthWrite(true);
	//aSettings.SetClearDepth(true);
	//aSettings.SetPolygonOffset(Graphic3d_PolygonOffset());
	//myViewer->SetZLayerSettings(andId,aSettings);

	//Handle(Graphic3d_ArrayOfPoints) anArray = new Graphic3d_ArrayOfPoints(theVerticiesMaxCount);
	//// add vertices to the array 
	//anArray->AddVertex(10.0, 10.0, 10.0);
	//anArray->AddVertex(0.0, 10.0, 10.0);
	//// add the array to the structure 
	//Handle(Graphic3d_Group) aGroup = myViewer->NewGroup();
	//aGroup->AddPrimitiveArray(anArray);
	//aGroup->SetGroupPrimitivesAspect(myDrawer->PointAspect()->Aspect());




}

//继承窗口Template
void CmOCCTDoc::On32831()
{
	CMethodDlg dlg;
	dlg.DoModal();

}
//继承窗口CMethodDlg2
void CmOCCTDoc::On32832()
{
	CMethodDlg2 dlg;
	dlg.DoModal();
}
//视图继承问题
void CmOCCTDoc::On32833()
{

}
