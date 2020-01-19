
// mOCCTView.cpp: CmOCCTView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "mOCCT.h"
#endif

#include "mOCCTDoc.h"
#include "mOCCTView.h"
#include <Geom_Curve.hxx>

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
#include"GSL_SVD.h"
#include<stdlib.h>
#include<stdio.h>
#include<gsl/gsl_vector.h>
#include<gsl/gsl_multiroots.h>
#include<conio.h>
#include"TNT_Test.h"
#include"./include/basics.h"
#include"./include/circle2d_fit.h"

#include"ISession_Coordinates.h"

#include"AIS_Text.h"
#include"ConvertToString.h"
#include<Resource_Unicode.hxx>
gp_Pln agpPlane;
// CmOCCTView

IMPLEMENT_DYNCREATE(CmOCCTView, CView)

BEGIN_MESSAGE_MAP(CmOCCTView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_shepe, &CmOCCTView::OnDrawshepe)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_XYZ_XYZ, &CmOCCTView::OnXyzXyz)
	ON_COMMAND(ID_32778, &CmOCCTView::On32778)
	ON_COMMAND(ID_32779, &CmOCCTView::On32779)
	ON_COMMAND(ID_32780, &CmOCCTView::On32780)
	ON_COMMAND(ID_32781, &CmOCCTView::On32781)
	ON_COMMAND(ID_DRAW_32782, &CmOCCTView::OnDraw32782)

	ON_COMMAND(ID_DRAW_32784, &CmOCCTView::OnDraw32784)
	ON_COMMAND(ID_DRAW_32785, &CmOCCTView::OnDraw32785)
	ON_COMMAND(ID_DRAW_32786, &CmOCCTView::OnDraw32786)
	ON_COMMAND(ID_32787, &CmOCCTView::On32787)
	ON_COMMAND(ID_DRAW_LINE, &CmOCCTView::OnDrawLine)
	ON_WM_LBUTTONUP()
	

	ON_COMMAND(ID_32793, &CmOCCTView::On32793)
	ON_COMMAND(ID_GSL_SVD32824, &CmOCCTView::OnGslSvd32824)
	ON_COMMAND(ID_GSL_TEST, &CmOCCTView::OnGslTest)
	ON_COMMAND(ID_TNT_TEST, &CmOCCTView::OnTntTest)
	ON_COMMAND(ID_MYDLL_BASIC, &CmOCCTView::OnMydllBasic)
	ON_COMMAND(ID_MYDLL_CIRCLE2D, &CmOCCTView::OnMydllCircle2d)
	ON_COMMAND(ID_32829, &CmOCCTView::On32829)
	ON_COMMAND(ID_32830, &CmOCCTView::On32830)

	ON_COMMAND(ID_32834, &CmOCCTView::On32834)
	ON_COMMAND(ID_32835, &CmOCCTView::On32835)
	ON_COMMAND(ID_32836, &CmOCCTView::On32836)
	ON_COMMAND(ID_HELP, &CmOCCTView::OnHelp)
	ON_COMMAND(ID_32840, &CmOCCTView::On32840)
	ON_COMMAND(ID_32841, &CmOCCTView::On32841)
	ON_COMMAND(ID_32842, &CmOCCTView::On32842)
END_MESSAGE_MAP()

// CmOCCTView 构造/析构

CmOCCTView::CmOCCTView()noexcept

{
	// TODO: 在此处添加构造代码
	m_shepe = FALSE;
	m_Zoom = FALSE;
	m_Rota = FALSE;
	m_Move = FALSE;
	m_JBZoom = FALSE;
	myXmax=0;
	myYmax=0;
	m_cylinder = FALSE;
	m_box = FALSE;
	m_cone = FALSE;
	m_torus = FALSE;
	m_light = FALSE;
	m_line = FALSE;




}

CmOCCTView::~CmOCCTView()
{
}

BOOL CmOCCTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CmOCCTView 绘图
// CmOCCTView 打印

BOOL CmOCCTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CmOCCTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CmOCCTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CmOCCTView 诊断

#ifdef _DEBUG
void CmOCCTView::AssertValid() const
{
	CView::AssertValid();
}

void CmOCCTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmOCCTDoc* CmOCCTView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmOCCTDoc)));
	return (CmOCCTDoc*)m_pDocument;
}
#endif //_DEBUG


// CmOCCTView 消息处理程序
void CmOCCTView::OnInitialUpdate() {
	myView = GetDocument()->GetViewer()->CreateView();
	myView->SetShadingModel(V3d_GOURAUD);
	Handle(Graphic3d_GraphicDriver) theGraphicDriver = ((CmOCCTApp*)AfxGetApp())->GetGraphicDriver();
	Aspect_Handle aWindowHandle = (Aspect_Handle)GetSafeHwnd();
	Handle(WNT_Window) aWntWindow = new WNT_Window(GetSafeHwnd());
	myView->SetWindow(aWntWindow);
	if (!aWntWindow->IsMapped()) {
		aWntWindow->Map();
	}
	Standard_Integer w = 100;
	Standard_Integer h = 100;
	aWntWindow->Size(w, h);
	::PostMessage(GetSafeHwnd(), WM_SIZE, SIZE_RESTORED, w + h * 65536);
	myView->FitAll();

	myView->ZBufferTriedronSetup(Quantity_NOC_RED, Quantity_NOC_GREEN, Quantity_NOC_BLUE1, 0.8, 0.05, 12);

	//坐标
	myView->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_WHITE, 0.2, V3d_ZBUFFER);//位置，颜色，缩放长度
	//myView->TriedronDisplay(Aspect_TOTP_CENTER, Quantity_NOC_BLACK, 0.2, V3d_ZBUFFER);

	

}


void CmOCCTView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnMouseMove(nFlags, point);

	if (nFlags && MK_LBUTTON) 
	{
		//选转
		if (m_Rota == TRUE)
		{
			myView->Rotate(point.x-myXmax, myYmax-point.y);
			myXmax = point.x;
			myYmax = point.y;
			//myView->Redraw();
			m_Zoom = FALSE;
			m_Move = FALSE;
		}
		//缩放
		if (m_Zoom == TRUE)
		{
			myView->Zoom(myXmax, myYmax, point.x, point.y);
			myXmax = point.x;  
			myYmax = point.y;
			m_Rota = FALSE;
			m_Move = FALSE;
		}
		//移动
		if (m_Move == TRUE)
		{
			myView->Pan(point.x-myXmax,myYmax-point.y);
			myXmax = point.x;
			myYmax = point.y;
			m_Zoom = FALSE;
			m_Rota = FALSE;			
		}
		//局部放大
		if (m_JBZoom == TRUE)
		{
			myXmax = point.x; myYmax = point.y;

		}
	}
	//实现高亮
	if (nFlags & MK_SHIFT)
	{
		
	}
	else
	{
		GetDocument()->MoveEvent(point.x,point.y,myView);
    }

}
void CmOCCTView::OnDraw(CDC* /*pDC*/)
{
	CmOCCTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	myView->MustBeResized();
	myView->Update();

	//画球
	if (m_shepe == TRUE)
	{
		pDoc->DrawSphere();
		m_shepe = FALSE;
	}
	//画圆柱
	if (m_cylinder == TRUE)
	{
		pDoc->make_cylinder(100.0,200.0);
		m_cylinder= FALSE;
	}
	//画正方形
	if (m_box == TRUE)
	{
		pDoc->OnDrawBox();
		m_box = FALSE;
	}
	//画圆锥
	if (m_cone == TRUE)
	{
		pDoc->MakeCone();
		m_cone = FALSE;
	}
	//画圆环
	if (m_torus == TRUE)
	{
		pDoc->Drawtorus();
		m_torus = FALSE;
	}
	//直线
	if (m_line == TRUE)
	{
		pDoc->OnLine();
		m_line = FALSE;
	}



}

void CmOCCTView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CView::OnLButtonDown(nFlags, point);
	myXmin = point.x;  myYmin = point.y;
	myXmax = point.x;  myYmax = point.y;
	//if (nFlags & MK_SHIFT)
	//	//GetDocument()->ShiftDragEvent(myXmax, myYmax, -1, myView);
	//else
		GetDocument()->DragEvent(myXmax, myYmax, -1, myView);
	//	ConvertClickToPoint(point.x,point.y,myView);
}

//缩放
void CmOCCTView::OnXyzXyz()
{
	// TODO: 在此添加命令处理程序代码
	m_Zoom = TRUE;
	m_Rota = FALSE;
}

//还原
void CmOCCTView::On32778()
{
	// TODO: 在此添加命令处理程序代码
	//还原缩小
	myView->Reset();
	m_Zoom = FALSE;
	m_Rota = FALSE;
	m_shepe = FALSE;
	m_JBZoom = FALSE;
	m_Move = FALSE;
}

//旋转
void CmOCCTView::On32779()
{
	// TODO: 在此添加命令处理程序代码
	m_Rota= TRUE;
	m_Zoom = FALSE;
}
//局部放大
void CmOCCTView::On32780()
{
	// TODO: 在此添加命令处理程序代码
	m_JBZoom = TRUE;
}

//移动
void CmOCCTView::On32781()
{
	// TODO: 在此添加命令处理程序代码
	m_Move = TRUE;
	m_Rota = FALSE;
	m_Zoom = FALSE;
}
//画球
void CmOCCTView::OnDrawshepe()
{
	// TODO: 在此添加命令处理程序代码
	m_shepe = TRUE;
	m_cylinder = FALSE;
	m_box = FALSE;
	Invalidate();
}
//画圆柱
void CmOCCTView::OnDraw32782()
{
	// TODO: 在此添加命令处理程序代码
	m_cylinder = TRUE;
	m_shepe = FALSE;
	m_box = FALSE;
	Invalidate();
}

//画正方形
void CmOCCTView::OnDraw32784()
{
	// TODO: 在此添加命令处理程序代码
	m_box = TRUE;
	m_cylinder = FALSE;
	m_shepe = FALSE;
	Invalidate();
}

//画圆锥
void CmOCCTView::OnDraw32785()
{
	// TODO: 在此添加命令处理程序代码
	m_cone = TRUE;
	m_box = FALSE;
	m_cylinder = FALSE;
	m_shepe = FALSE;
	Invalidate();
}

//画圆环
void CmOCCTView::OnDraw32786()
{
	// TODO: 在此添加命令处理程序代码
	m_torus = TRUE;
	m_cone = FALSE;
	m_box = FALSE;
	m_cylinder = FALSE;
	m_shepe = FALSE;
	Invalidate();
}

//高亮
void CmOCCTView::On32787()
{
	// TODO: 在此添加命令处理程序代码
	m_light = TRUE;
	m_Move = FALSE;
	m_Rota = FALSE;
	m_Zoom = FALSE;
}

//线
void CmOCCTView::OnDrawLine()
{
	// TODO: 在此添加命令处理程序代码
	m_line = true;
	m_torus = FALSE;
	m_cone = FALSE;
	m_box = FALSE;
	m_cylinder = FALSE;
	m_shepe = FALSE;
	Invalidate();
}

void CmOCCTView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nFlags & MK_CONTROL)
	{
		return;
	}
	else // if ( Ctrl )
	{
		if (point.x == myXmin && point.y == myYmin)
		{ // no offset between down and up --> selectEvent
			myXmax = point.x;
			myYmax = point.y;
				GetDocument()->InputEvent(point.x, point.y, myView);
		}
	}

	CView::OnLButtonUp(nFlags, point);
}
//透明线框
void CmOCCTView::On32793()
{
	// TODO: 在此添加命令处理程序代码
	GetDocument()->GetAISContext()->SetDisplayMode(AIS_WireFrame, Standard_True);
	myView->SetComputedMode(Standard_False);
	myView->Redraw();
}


//gp_Pnt CmOCCTView::ChangeCoordinateSecond(double x,double y)
//{
	// TODO: 在此处添加实现代码.
	//gp_Pnt P0, P1, P3;
	//gp_Vec Vp2; 
	//Handle(Geom_Curve) aCurve;	
	//double X, Y, Z, VX, VY, VZ;
	//myView->Convert(int(x), int(y), X, Y, Z);
	//myView->Proj(VX, VY, VZ);	
	//P1.SetCoord(X, Y, Z);	
	//Vp2.SetCoord(VX, VY, VZ);	
	//gp_Lin gpLin(P1, gp_Dir(Vp2));
	//aCurve=GC_MakeSegment(gpLin,-100,100);
	//
	//TopLoc_Location location;
	//Handle(Geom_Surface) aGeometricSurface = BRep_Tool::Surface(F, location);
	//GeomAPI_IntCS CS(aCurve, aGeometricSurface);   //aGeometricSurface为与直线相交的面 	
	//Standard_Integer NbSeg = 0;	
	//Standard_Integer NbPoints = 0;
	//Handle(Geom_Curve) segment;	
	//if(CS.IsDone())	
	//{		
	//	NbSeg = CS.NbSegments();	
	//	for (Standard_Integer k=1; k<=NbSeg; k++)	
	//	{			
	//		segment = CS.Segment(k);	
	//	} 		
	//	NbPoints = CS.NbPoints();	
	//	for (int k=1; k<=NbPoints; k++)		
	//	{			
	//		gp_Pnt aPoint=CS.Point(k);	
	//		P3=aPoint;	
	//	}	}	
	//return P3;

//}

gp_Vec CmOCCTView::NormalVector(TopoDS_Face F)
{
	// TODO: 在此处添加实现代码.
	TopLoc_Location location;
	Handle(Geom_Surface) aGeometricSurface = BRep_Tool::Surface(F,location);
	Handle(Geom_Plane) aPlane = Handle(Geom_Plane)::DownCast(aGeometricSurface);
	agpPlane = aPlane->Pln();
	gp_Ax1 norm = agpPlane.Axis();
	gp_Dir dir = norm.Direction();
	gp_Vec move = gp_Vec(dir);
	return move;
}
gp_Pnt ConvertClickToPoint(Standard_Real x, Standard_Real y, Handle(V3d_View) aView)
{
	gp_Pln PlaneOfTheView = agpPlane;  
	//注意agpPlane是全局变量，创建一个平面，                                  
	//用于将鼠标点投射在此面上，这是将鼠标点投射在选定面上的      
	//基础    
	Standard_Real X,Y,Z;  
	aView->Convert(int(x),int(y),X,Y,Z); 
	//将鼠标点坐标转换为OCC三维坐标   
	gp_Pnt ConvertedPoint(X,Y,Z);   
	gp_Pnt2d ConvertedPointOnPlane =ProjLib::Project(PlaneOfTheView,ConvertedPoint);   
	gp_Pnt ResultPoint = ElSLib::Value(ConvertedPointOnPlane.X(),  
		ConvertedPointOnPlane.Y(),        PlaneOfTheView);    
	return ResultPoint;    
	//将鼠标点二维坐标转换为基于OCC三维坐标选定面上的坐标（OCC三维
}
//GSL is Test
void CmOCCTView::OnGslTest()
{
	const size_t n = 2;
	gsl_vector *x = gsl_vector_alloc(n);
	double x_init[2] = {-10.0,-5.0};
	gsl_vector_set(x,0,x_init[0]);
	gsl_vector_set(x,1,x_init[1]);
	gsl_vector_free(x);
	_cprintf("Test!\n",x);
	getchar();
}
//加载奇异值分解对话框
void CmOCCTView::OnGslSvd32824()
{
	GSL_SVD dlg;
	dlg.DoModal();
}
//加载TNT
void CmOCCTView::OnTntTest()
{
	TNT_Test dlg;
	dlg.DoModal();
}
//坐标装换成3D坐标
void CmOCCTView::On32829()
{
		//1.view中具有的物体形状
//		myAISContext->Deactivate();
//		myAISContext->Activate(AIS_Shape::SelectionMode(TopAbs_FACE));
		//2.鼠标选中的面高亮
		GetDocument()->DragEvent(myXmax, myYmax, -1, myView);
		
		//3.鼠标选中高亮的区域转换成面
		gp_Pln aFacePlane(gp_Pnt(0.1, 0.0, 0.0), gp_Dir(1.0, 0.0, 0.0));
		BRepBuilderAPI_MakeFace aMakeFaceCommand(aFacePlane, 200.0, -200.0, 410.0, -410.0);
		TopoDS_Face aShape = aMakeFaceCommand.Face();

		//TopoDS_Face aShape = BRepBuilderAPI_MakeFace(W1.Wire());
		//TopoDS_Face aShape = BRepBuilderAPI_MakeFace(myXmax, myYmax, -1, myView);
		

	

}
void CmOCCTView::OnMydllBasic()
{
	
}

void CmOCCTView::OnMydllCircle2d()
{
	
}


//测试头
void CmOCCTView::On32830()
{
	double m_fRadius = 10;
	double m_ProbePoleLength = 20.0;
	Graphic3d_MaterialAspect myRubyMat;

	Handle(AIS_InteractiveContext)ais_context = ((CmOCCTDoc*)GetDocument())->GetAISContext();

	Handle(AIS_Shape)	mySphere;
	Handle(AIS_Shape)	myCylinder1;
	Handle(AIS_Shape)	myCylinder2;
	Handle(AIS_Shape)	myCylinder3;
	Handle(AIS_Shape)	myCone1;
	Handle(AIS_Shape)	myCone2;



	//球
	TopoDS_Shape S1 = BRepPrimAPI_MakeSphere(m_fRadius);
	mySphere = new AIS_Shape(S1);
	gp_Trsf myTransfo;
	myTransfo.SetTranslation(gp_Pnt(0, 0, 0), gp_Pnt(0, 0, 30));//以（0，0，0）转换
	ais_context->SetLocation(mySphere, myTransfo);
	ais_context->SetColor(mySphere, Quantity_NOC_GRAY, Standard_True);
	ais_context->Display(mySphere, Standard_False);

	//圆柱
	TopoDS_Shape C1 = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), m_fRadius / 2, m_ProbePoleLength / 2);
	myCylinder1 = new AIS_Shape(C1);
	gp_Ax3 from(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	gp_Ax3 to(gp_Pnt(0, 0, 35), gp_Dir(0, 0, 1));
	myTransfo.SetTransformation(to, from);
	ais_context->SetLocation(myCylinder1, myTransfo);
	ais_context->SetColor(myCylinder1, Quantity_NOC_GRAY, Standard_True);
	ais_context->Display(myCylinder1, Standard_True);

	//圆锥
	TopoDS_Shape A1 = BRepPrimAPI_MakeCone(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), m_fRadius / 2, m_fRadius*1.5, m_ProbePoleLength / 2);
	myCone1 = new AIS_Shape(A1);
	gp_Ax3 from1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	gp_Ax3 to1(gp_Pnt(0, 0, 45), gp_Dir(0, 0, 1));
	myTransfo.SetTransformation(to1, from1);
	ais_context->SetLocation(myCone1, myTransfo);
	ais_context->SetColor(myCone1, Quantity_NOC_GRAY, Standard_True);
	ais_context->Display(myCone1, Standard_True);

	//圆柱
	TopoDS_Shape C2 = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), m_fRadius* 1.5, m_fRadius * 3);
	myCylinder2 = new AIS_Shape(C2);
	gp_Ax3 from2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	gp_Ax3 to2(gp_Pnt(0, 0, 55), gp_Dir(0, 0, 1));
	myTransfo.SetTransformation(to2, from2);
	ais_context->SetLocation(myCylinder2, myTransfo);
	ais_context->SetColor(myCylinder2, Quantity_NOC_GRAY, Standard_True);
	ais_context->Display(myCylinder2, Standard_True);

	//圆锥
	TopoDS_Shape A2 = BRepPrimAPI_MakeCone(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), m_fRadius*1.5, m_fRadius * 3, m_fRadius * 2);
	myCone2 = new AIS_Shape(A2);
	gp_Ax3 from3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	gp_Ax3 to3(gp_Pnt(0, 0, 75), gp_Dir(0, 0, 1));
	myTransfo.SetTransformation(to3, from3);
	ais_context->SetLocation(myCone2, myTransfo);
	ais_context->SetColor(myCone2, Quantity_NOC_GRAY, Standard_True);
	ais_context->Display(myCone2, Standard_True);

	//圆柱
	TopoDS_Shape C3 = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), m_fRadius * 3, m_fRadius * 3);
	myCylinder3 = new AIS_Shape(C3);
	gp_Ax3 from4(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	gp_Ax3 to4(gp_Pnt(0, 0, 95), gp_Dir(0, 0, 1));
	myTransfo.SetTransformation(to4, from4);
	ais_context->SetLocation(myCylinder3, myTransfo);
	ais_context->SetColor(myCylinder3, Quantity_NOC_GRAY, Standard_True);
	ais_context->Display(myCylinder3, Standard_True);


}

//画瓶子
TopoDS_Shape  CmOCCTView::MakeBottle(const Standard_Real myWidth, const Standard_Real myHeight,
	const Standard_Real myThickness)
{
	
	// 轮廓：定义支持点。在XOY平面中找出底部5个点
	gp_Pnt aPnt1(-myWidth / 2., 0, 0);
	gp_Pnt aPnt2(-myWidth / 2., -myThickness / 4., 0);
	gp_Pnt aPnt3(0, -myThickness / 2., 0);
	gp_Pnt aPnt4(myWidth / 2., -myThickness / 4., 0);
	gp_Pnt aPnt5(myWidth / 2., 0, 0);

	// 轮廓：定义几何图形。2个线段，1个圆弧
	Handle(Geom_TrimmedCurve) anArcOfCircle = GC_MakeArcOfCircle(aPnt2, aPnt3, aPnt4);
	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(aPnt1, aPnt2);
	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(aPnt4, aPnt5);

	// 轮廓：定义拓扑结构。3条边和1条线，TopoDS定义了几何实体之间的关系来表示复杂的形状
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(anArcOfCircle);
	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(aSegment2);
	TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(anEdge1, anEdge2, anEdge3);

	// 完成轮廓。反射现有的线来计算新的线
	gp_Ax1 xAxis = gp::OX();//获得X轴
	gp_Trsf aTrsf;

	aTrsf.SetMirror(xAxis);
	BRepBuilderAPI_Transform aBRepTrsf(aWire, aTrsf);
	TopoDS_Shape aMirroredShape = aBRepTrsf.Shape();
	TopoDS_Wire aMirroredWire = TopoDS::Wire(aMirroredShape);

	BRepBuilderAPI_MakeWire mkWire;
	mkWire.Add(aWire);
	mkWire.Add(aMirroredWire);
	TopoDS_Wire myWireProfile = mkWire.Wire();

	// 瓶身：拉伸轮廓。Prism功能，一个形状和方形作为输入
	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(myWireProfile);
	gp_Vec aPrismVec(0, 0, myHeight);
	TopoDS_Shape myBody = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);

	// 瓶身：倒角 ？？？
	BRepFilletAPI_MakeFillet mkFillet(myBody);
	TopExp_Explorer anEdgeExplorer(myBody, TopAbs_EDGE);
	while (anEdgeExplorer.More()) {
		TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer.Current());
		//Add edge to fillet algorithm
		mkFillet.Add(myThickness / 12., anEdge);
		anEdgeExplorer.Next();
	}

	myBody = mkFillet.Shape();

	// 瓶身 : 添加瓶颈
	gp_Pnt neckLocation(0, 0, myHeight);
	gp_Dir neckAxis = gp::DZ();
	gp_Ax2 neckAx2(neckLocation, neckAxis);

	Standard_Real myNeckRadius = myThickness / 4.;
	Standard_Real myNeckHeight = myHeight / 10.;

	BRepPrimAPI_MakeCylinder MKCylinder(neckAx2, myNeckRadius, myNeckHeight);
	TopoDS_Shape myNeck = MKCylinder.Shape();

	myBody = BRepAlgoAPI_Fuse(myBody, myNeck);

	//瓶身：创造中空的实体
	TopoDS_Face   faceToRemove;
	Standard_Real zMax = -1;

	for (TopExp_Explorer aFaceExplorer(myBody, TopAbs_FACE); aFaceExplorer.More(); aFaceExplorer.Next()) {
		TopoDS_Face aFace = TopoDS::Face(aFaceExplorer.Current());
		// Check if <aFace> is the top face of the bottle抯 neck 
		Handle(Geom_Surface) aSurface = BRep_Tool::Surface(aFace);
		if (aSurface->DynamicType() == STANDARD_TYPE(Geom_Plane)) {
			Handle(Geom_Plane) aPlane = Handle(Geom_Plane)::DownCast(aSurface);
			gp_Pnt aPnt = aPlane->Location();
			Standard_Real aZ = aPnt.Z();
			if (aZ > zMax) {
				zMax = aZ;
				faceToRemove = aFace;
			}
		}
	}

	TopTools_ListOfShape facesToRemove;
	facesToRemove.Append(faceToRemove);
	BRepOffsetAPI_MakeThickSolid BodyMaker;
	BodyMaker.MakeThickSolidByJoin(myBody, facesToRemove, -myThickness / 50, 1.e-3);
	myBody = BodyMaker.Shape();

	//myBody = BRepOffsetAPI_MakeThickSolid(myBody, facesToRemove, -myThickness / 50, 1.e-3);
	// Threading : Create Surfaces
	Handle(Geom_CylindricalSurface) aCyl1 = new Geom_CylindricalSurface(neckAx2, myNeckRadius * 0.99);
	Handle(Geom_CylindricalSurface) aCyl2 = new Geom_CylindricalSurface(neckAx2, myNeckRadius * 1.05);

	// Threading : Define 2D Curves
	gp_Pnt2d aPnt(2. * M_PI, myNeckHeight / 2.);
	gp_Dir2d aDir(2. * M_PI, myNeckHeight / 4.);
	gp_Ax2d anAx2d(aPnt, aDir);

	Standard_Real aMajor = 2. * M_PI;
	Standard_Real aMinor = myNeckHeight / 10;

	Handle(Geom2d_Ellipse) anEllipse1 = new Geom2d_Ellipse(anAx2d, aMajor, aMinor);
	Handle(Geom2d_Ellipse) anEllipse2 = new Geom2d_Ellipse(anAx2d, aMajor, aMinor / 4);
	Handle(Geom2d_TrimmedCurve) anArc1 = new Geom2d_TrimmedCurve(anEllipse1, 0, M_PI);
	Handle(Geom2d_TrimmedCurve) anArc2 = new Geom2d_TrimmedCurve(anEllipse2, 0, M_PI);
	gp_Pnt2d anEllipsePnt1 = anEllipse1->Value(0);
	gp_Pnt2d anEllipsePnt2 = anEllipse1->Value(M_PI);

	Handle(Geom2d_TrimmedCurve) aSegment = GCE2d_MakeSegment(anEllipsePnt1, anEllipsePnt2);
	// Threading : Build Edges and Wires
	TopoDS_Edge anEdge1OnSurf1 = BRepBuilderAPI_MakeEdge(anArc1, aCyl1);
	TopoDS_Edge anEdge2OnSurf1 = BRepBuilderAPI_MakeEdge(aSegment, aCyl1);
	TopoDS_Edge anEdge1OnSurf2 = BRepBuilderAPI_MakeEdge(anArc2, aCyl2);
	TopoDS_Edge anEdge2OnSurf2 = BRepBuilderAPI_MakeEdge(aSegment, aCyl2);
	TopoDS_Wire threadingWire1 = BRepBuilderAPI_MakeWire(anEdge1OnSurf1, anEdge2OnSurf1);
	TopoDS_Wire threadingWire2 = BRepBuilderAPI_MakeWire(anEdge1OnSurf2, anEdge2OnSurf2);
	BRepLib::BuildCurves3d(threadingWire1);
	BRepLib::BuildCurves3d(threadingWire2);

	// Create Threading 
	BRepOffsetAPI_ThruSections aTool(Standard_True);
	aTool.AddWire(threadingWire1);
	aTool.AddWire(threadingWire2);
	aTool.CheckCompatibility(Standard_False);

	TopoDS_Shape myThreading = aTool.Shape();

	// Building the Resulting Compound 
	TopoDS_Compound aRes;
	BRep_Builder aBuilder;
	aBuilder.MakeCompound(aRes);
	aBuilder.Add(aRes, myBody);
	aBuilder.Add(aRes, myThreading);

	Handle(AIS_Shape) ais2 = new AIS_Shape(aRes);
	GetDocument()->GetAISContext()->SetColor(ais2, Quantity_NOC_GRAY, Standard_False);
	GetDocument()->GetAISContext()->SetMaterial(ais2, Graphic3d_NOM_GOLD, Standard_False);
	GetDocument()->GetAISContext()->Display(ais2, Standard_True);

	
}

//瓶子
void CmOCCTView::On32834()
{
	TopoDS_Shape t_topo_bottle = MakeBottle(70.0, 50.0, 30.0);
	Handle(AIS_Shape) t_ais_bottle = new AIS_Shape(t_topo_bottle);
	GetDocument()->GetAISContext()->Display(t_ais_bottle, Standard_True);
	myView->FitAll();


}
//测试头
void CmOCCTView::On32835()
{
	double m_fRadius = 10;
	double m_ProbePoleLength = 20.0;
	Graphic3d_MaterialAspect myRubyMat;

	Handle(AIS_InteractiveContext)ais_context = ((CmOCCTDoc*)GetDocument())->GetAISContext();

	
	Handle(AIS_Shape)	ProbePole;
	TopoDS_Shape S1 = BRepPrimAPI_MakeSphere(gp_Pnt(0, 0, 30), m_fRadius);
	TopoDS_Shape C1 = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 35), gp_Dir(0, 0, 1)), m_fRadius / 2, m_ProbePoleLength / 2);
	TopoDS_Shape body1Part = BRepAlgoAPI_Fuse(S1, C1);

	TopoDS_Shape A1 = BRepPrimAPI_MakeCone(gp_Ax2(gp_Pnt(0, 0, 45), gp_Dir(0, 0, 1)), m_fRadius / 2, m_fRadius*1.5, m_ProbePoleLength / 2);
	TopoDS_Shape C2 = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 55), gp_Dir(0, 0, 1)), m_fRadius* 1.5, m_fRadius * 3);
	TopoDS_Shape body2Part = BRepAlgoAPI_Fuse(A1, C2);

	TopoDS_Shape A2 = BRepPrimAPI_MakeCone(gp_Ax2(gp_Pnt(0, 0, 75), gp_Dir(0, 0, 1)), m_fRadius*1.5, m_fRadius * 3, m_fRadius * 2);
	TopoDS_Shape C3 = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 95), gp_Dir(0, 0, 1)), m_fRadius * 3, m_fRadius * 3);
	TopoDS_Shape body3Part = BRepAlgoAPI_Fuse(A2, C3);

	TopoDS_Shape Body1= BRepAlgoAPI_Fuse(body1Part, body2Part);
	TopoDS_Shape body = BRepAlgoAPI_Fuse(Body1, body3Part);
	ProbePole = new AIS_Shape(body);
	ais_context->SetColor(ProbePole, Quantity_NOC_GRAY, Standard_True);
	ais_context->Display(ProbePole, Standard_True);

}

//测试头走10mm
void CmOCCTView::On32836()
{
	myView->Pan(10, 10);
}

#include "htmlhelp.h"
void CmOCCTView::OnHelp()
{
	CString strHelp;
	strHelp = _T("E:\\TestHtmlHelp\\Test.chm");
	char charHelp[MAX_PATH];
	int len = WideCharToMultiByte(CP_ACP, 0, strHelp, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)strHelp, -1, charHelp, len, NULL, NULL);
	HWND helpwnd = ::HtmlHelp(GetSafeHwnd(),(LPCWSTR)charHelp, HH_DISPLAY_TOPIC, NULL);
}



#include <Draw_Interpretor.hxx>
#include<Quantity_Parameter.hxx>
static int VDrawText(Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
	// Check arguments
	if (argc < 14)
	{
		di << "Error: " << argv[0] << " - invalid number of arguments\n";
		di << "Usage: type help " << argv[0] << "\n";
		return 1; //TCL_ERROR
	}


	// Text position
//	const Standard_Real X = Atof(argv[2]);
//	const Standard_Real Y = Atof(argv[3]);
//	const Standard_Real Z = Atof(argv[4]);
//	const gp_Pnt pnt(X, Y, Z);

	// Text color
//	const Quantity_Parameter R = Atof(argv[5]) / 255.;
//	const Quantity_Parameter G = Atof(argv[6]) / 255.;
//	const Quantity_Parameter B = Atof(argv[7]) / 255.;
//	const Quantity_Color aColor(R, G, B, Quantity_TOC_RGB);

	// Text alignment
//	const int hor_align = Atoi(argv[8]);
//	const int ver_align =Atoi(argv[9]);

	// Text angle
	const Standard_Real angle = Atof(argv[10]);

	// Text zooming
	//const Standard_Boolean zoom =Atoi(argv[11]);

	// Text height
	const Standard_Real height = Atof(argv[12]);

	// Text aspect
	//const Font_FontAspect aspect = Font_FontAspect(Atoi(argv[13]));

	// Text font
	TCollection_AsciiString font;
	if (argc < 15)
		font.AssignCat("Courier");
	else
		font.AssignCat(argv[14]);

	// Text is multibyte
//	const Standard_Boolean isMultibyte = (argc < 16) ? Standard_False : (Atoi(argv[15]) != 0);

	// Read text string
	TCollection_ExtendedString name;
	//if (isMultibyte)
	//{
		/* eryar modified 20140817 11:11
	  const char *str = argv[1];
	  while ( *str || *(str+1)=='\x0A' || *(str+1)=='\x0B' || *(str+1)=='\x0C' || *(str+1)=='\x0D'
				   || *(str+1)=='\x07' || *(str+1)=='\x08' || *(str+1)=='\x09' )
	  {
		unsigned short c1 = *str++;
		unsigned short c2 = *str++;
		if (!c2) break;
		name += (Standard_ExtCharacter)((c1 << 8) | c2);
	  }
	  */
//		Resource_Unicode::ConvertGBToUnicode(argv[1], name);
	//}
//	else
	//{
	//	name += argv[1];
	//}

	if (name.Length())
	{
//		Handle(AIS_InteractiveContext)aContext = ((CmOCCTDoc*)GetDocument())->GetAISContext();
//		Handle(AIS_Text) myT = new AIS_Text(name, pnt, aColor, angle, height,font.ToCString());
	//	aContext->Display(myT, Standard_True);
	}

	return 0;
}



void CmOCCTView::On32840()
{
	Standard_CString aText = "点";//"&#x70B9";// "\u70b9"

	TCollection_ExtendedString name;
	const gp_Pnt pnt(0, 0, 0);
//	const Quantity_Color aColor(255, 255, 255, Quantity_TOC_RGB);
	//const Standard_Real angle = 0;
	//const Standard_Real height = 100;

	//TCollection_AsciiString font;
	
	//if (argc < 15)
	//	font.AssignCat("Courier");
//	else
	//	font.AssignCat("SimHei");

	Resource_Unicode::ConvertGBToUnicode("P终于可以了-点", name);

	Handle(AIS_InteractiveContext)aContext = ((CmOCCTDoc*)GetDocument())->GetAISContext();
	//Handle(AIS_Text) myT = new AIS_Text(name, pnt, angle, height, font.ToCString());
	Handle(AIS_Text) myT = new AIS_Text();
	myT->SetFont();
	myT->SetText(name);
	myT->SetHeight(50);
	myT->SetAngle();
	aContext->Display(myT, Standard_True);
	
}

void CmOCCTView::On32841()
{
	ConvertToString dlg;
	dlg.DoModal();
}










#include<ft2build.h>
#include FT_FREETYPE_H
#pragma comment(lib,"freetype.lib")
//freetype
//v 包含头文件 Header Files;
//v 库的初始化 Library Initialization;
//v 加载字体 Loading a Font Face;
//v 访问字体数据 Accessing the Face Data;
//v 设置当前像素大小 Setting the Current Pixel Size;
//v 加载文字 Loading a Glyph Image;
//v 简单的显示 Simple Text Rendering；

#include <BRepTools.hxx>

#include <Font_BRepFont.hxx>
#include <Font_BRepTextBuilder.hxx>

#pragma comment(lib, "TKernel.lib")
#pragma comment(lib, "TKMath.lib")

#pragma comment(lib, "TKG2d.lib")
#pragma comment(lib, "TKG3d.lib")
#pragma comment(lib, "TKGeomBase.lib")
#pragma comment(lib, "TKGeomAlgo.lib")

#pragma comment(lib, "TKBRep.lib")
#pragma comment(lib, "TKTopAlgo.lib")

#pragma comment(lib, "TKService.lib")
#include<Resource_Unicode.hxx>
void CmOCCTView::On32842()
{
	FT_Face aFace = NULL;
	FT_Library aLibrary = NULL;
	FT_Init_FreeType(&aLibrary);

	FT_New_Face(aLibrary, "C:/Windows/Fonts/arial.ttf", 0, &aFace);
	FT_Set_Char_Size(aFace,0,16*64,300,300);

	FT_UInt aGlyphIndex = FT_Get_Char_Index(aFace,'点');
	//FT_Load_Glyph(aFace,aGlyphIndex,FT_LOAD_DEFAULT);

	FT_GlyphSlot aGlyphSlot = aFace->glyph;


	//Font_BRepFont aBrepFont("C:/Windows/Fonts/arial.ttf", 3.5);
	Font_BRepFont aBrepFont("C:/Windows/Fonts/SimSun.ttf", 35);
	Font_BRepTextBuilder aTextBuilder;
	TopoDS_Shape aTextShape = aTextBuilder.Perform(aBrepFont, NCollection_String("你哈 Joyce点"));

	BRepTools::Dump(aTextShape, std::cout);
	BRepTools::Write(aTextShape, "d:/text.brep");

	Handle(AIS_Shape) text = new AIS_Shape(aTextShape);
	Handle(AIS_InteractiveContext)ais_context = ((CmOCCTDoc*)GetDocument())->GetAISContext();
	ais_context->Display(text, Standard_True);



}
