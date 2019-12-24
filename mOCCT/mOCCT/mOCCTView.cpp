
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
	//ON_COMMAND(ID_DRAW_32820, &CmOCCTView::OnDraw32820)
	ON_COMMAND(ID_GSL_SVD32824, &CmOCCTView::OnGslSvd32824)
	ON_COMMAND(ID_GSL_TEST, &CmOCCTView::OnGslTest)
	ON_COMMAND(ID_TNT_TEST, &CmOCCTView::OnTntTest)
	ON_COMMAND(ID_MYDLL_BASIC, &CmOCCTView::OnMydllBasic)
	ON_COMMAND(ID_MYDLL_CIRCLE2D, &CmOCCTView::OnMydllCircle2d)
	ON_COMMAND(ID_32829, &CmOCCTView::On32829)
	//ON_COMMAND(ID_32830, &CmOCCTView::On32830)
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

