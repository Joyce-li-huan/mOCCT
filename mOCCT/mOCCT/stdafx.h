
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类

#include<BRepOffsetAPI_MakePipe.hxx>
#include<Geom_BezierCurve.hxx>
#include <GC_MakeEllipse.hxx>
#pragma comment(lib,"TKXSDRAW.lib")



#pragma warning(  disable : 4244 )        // Issue warning 4244
#include <Standard_ShortReal.hxx>
#pragma warning(  default : 4244 )        // Issue warning 4244

#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <AIS_ListOfInteractive.hxx>
#include <AIS_ListIteratorOfListOfInteractive.hxx>
#include <AIS_Shape.hxx>
#include <AIS_Trihedron.hxx>

#include <Aspect_Background.hxx>
#include <Aspect_TypeOfline.hxx>
#include <Aspect_WidthOfline.hxx>
#include <Aspect_Window.hxx>
#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>
#include <BRep_Builder.hxx>

#include <Prs3d_Presentation.hxx>
#include <Standard_Macro.hxx>
#include <Graphic3d_GraphicDriver.hxx>


#include "IGESControl_Reader.hxx"
#include <BRepAlgo.hxx> 
#include <BRepTools.hxx>  
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <Standard_DefineHandle.hxx>  
#include <DsgPrs_LengthPresentation.hxx>  
#include <GCPnts_TangentialDeflection.hxx>  
#include <Geom_Axis2Placement.hxx>  
#include <Geom_CartesianPoint.hxx>  
#include <Geom_Line.hxx>  
#include <Geom_Surface.hxx>  
#include <BRepAdaptor_Surface.hxx>  
#include <GeomAbs_CurveType.hxx>  
#include <GeomAdaptor_Curve.hxx>  
#include <GeomTools_Curve2dSet.hxx>  
#include <gp_Vec.hxx>  
#include <Graphic3d_NameOfMaterial.hxx>  
#include <MMgt_TShared.hxx>  
#include <OSD_Environment.hxx>  
#include <Precision.hxx>  
#include <Prs3d_IsoAspect.hxx>  
#include <Prs3d_LineAspect.hxx>  
#include <Prs3d_Projector.hxx>  
#include <Prs3d_Text.hxx>  
#include <Quantity_Factor.hxx>  
#include <Quantity_Length.hxx>  
#include <Quantity_NameOfColor.hxx>  
#include <Quantity_PhysicalQuantity.hxx>  
#include <Quantity_PlaneAngle.hxx>  
#include <Quantity_TypeOfColor.hxx>  
#include <SelectMgr_EntityOwner.hxx>  
#include <SelectMgr_SelectableObject.hxx>  
#include <SelectMgr_Selection.hxx>  
#include <SelectMgr_SelectionManager.hxx>  
#include <SelectMgr_ListOfFilter.hxx>  
#include <SelectMgr_Filter.hxx>  
#include <StdSelect_EdgeFilter.hxx>  
#include <StdSelect_ShapeTypeFilter.hxx>  
#include <Standard_Boolean.hxx>  
#include <Standard_CString.hxx>  
#include <Standard_ErrorHandler.hxx>  
#include <Standard_Integer.hxx>  
#include <Standard_IStream.hxx>  
#include <Standard_Macro.hxx>  
#include <Standard_NotImplemented.hxx>  
#include <Standard_OStream.hxx>  
#include <Standard_Real.hxx>  
#include <StdPrs_Curve.hxx>  
#include <StdPrs_Point.hxx>  
#include <StdPrs_PoleCurve.hxx>  
#include <TCollection_AsciiString.hxx>  
#include <TColgp_Array1OfPnt2d.hxx>  
#include <TColgp_HArray1OfPnt2d.hxx>  
#include <TCollection_AsciiString.hxx>  
#include <TColStd_HSequenceOfTransient.hxx>  
#include <TColStd_MapIteratorOfMapOfTransient.hxx>  
#include <TColStd_MapOfTransient.hxx>  
#include <TopExp_Explorer.hxx>  
#include <TopoDS.hxx>  
#include <TopoDS_Compound.hxx>  
#include <TopoDS_Shape.hxx>  
#include <TopoDS_Solid.hxx>  
#include <TopoDS_Vertex.hxx>  
#include <TopExp.hxx>  
#include <TopTools_HSequenceOfShape.hxx>  
#include <UnitsAPI.hxx>  
#include <V3d_View.hxx>  
#include <V3d_Viewer.hxx>  
#include <WNT_Window.hxx>  
#include <Prs3d_PointAspect.hxx>  
#include <AIS_Point.hxx>  
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <BRep_Tool.hxx>  
#include <BRepAlgoAPI_Fuse.hxx>  
#include <BRepBuilderAPI_MakeEdge.hxx>  
#include <BRepBuilderAPI_MakeFace.hxx>  
#include <BRepBuilderAPI_MakeWire.hxx>  
#include <BRepBuilderAPI_MakeVertex.hxx>  
#include <BRepBuilderAPI_Transform.hxx>  
#include <BRepPrimAPI_MakeCone.hxx>  
#include <BRepPrimAPI_MakeRevol.hxx>  
#include <BRepFilletAPI_MakeFillet.hxx>  
#include <BRepBuilderAPI_Copy.hxx>  
#include <BRepBuilderAPI_MakePolygon.hxx>  
#include <BRepLib.hxx>  
#include <BRepOffsetAPI_MakeThickSolid.hxx>  
#include <BRepOffsetAPI_ThruSections.hxx>  
#include <BRepPrimAPI_MakeCylinder.hxx>  
#include <BRepPrimAPI_MakePrism.hxx>  
#include <BRepPrimAPI_MakeTorus.hxx>  
#include <BRepAlgoAPI_Section.hxx>  
#include <BRepPrimAPI_MakeSphere.hxx>  
#include <BRepFeat_SplitShape.hxx>  
#include <TColgp_HArray1OfPnt.hxx>  
#include <GeomAPI_Interpolate.hxx>  
#include <GC_MakeArcOfCircle.hxx>  
#include <GC_MakeSegment.hxx>  
#include <GC_MakeCircle.hxx>  
#include <GCE2d_MakeSegment.hxx>  
#include <gp.hxx>  
#include <gp_Ax1.hxx>  
#include <gp_Ax2.hxx>  
#include <gp_Ax2d.hxx>  
#include <gp_Dir.hxx>  
#include <gp_Dir2d.hxx>  
#include <gp_Pnt.hxx>  
#include <gp_Pnt2d.hxx>  
#include <gp_Trsf.hxx>  
#include <Geom_CylindricalSurface.hxx>  
#include <Geom_Plane.hxx>  
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>  
#include <Geom_TrimmedCurve.hxx>  
#include <Geom2d_Ellipse.hxx>  
#include <Geom2d_TrimmedCurve.hxx>  
#include <TopExp_Explorer.hxx>  
#include <TopoDS.hxx>  
#include <TopoDS_Edge.hxx>  
#include <TopoDS_Face.hxx>  
#include <TopoDS_Wire.hxx>  
#include <TopoDS_Shape.hxx>  
#include <TopoDS_Compound.hxx>  
#include <GCPnts_AbscissaPoint.hxx>  
#include <BRepAdaptor_Curve.hxx>  
#include <GeomLib.hxx>  
#include <GeomConvert_CompCurveToBSplineCurve.hxx>  
#include <TopTools_ListOfShape.hxx>  
#include <TopTools_ListIteratorOfListOfShape.hxx>  
#include <TopTools_DataMapOfShapeInteger.hxx>  
#include <TopTools_DataMapOfShapeReal.hxx>  
#include <TopTools_IndexedDataMapOfShapeAddress.hxx>  
#include <V3d_PositionalLight.hxx>  
#include <V3d_DirectionalLight.hxx>  
#include <V3d_AmbientLight.hxx>  
#include <IGESControl_Controller.hxx>  
#include <IGESControl_Writer.hxx>  
#include <Interface_Static.hxx>  
#include <OpenGl_GraphicDriver.hxx>  
#include <Graphic3d_GraphicDriver.hxx>  

//画线
#include <AIS_Line.hxx>
#include<AIS_Circle.hxx>

#include<Geom_Ellipse.hxx>
#include<gp_Elips.hxx>
// specific STEP

#include <STEPControl_Controller.hxx>
#include <STEPControl_Reader.hxx>
#include <STEPControl_Writer.hxx>

// OCAF
#include <TDocStd_Document.hxx>
#include <TPrsStd_AISViewer.hxx>
#include <TDF_Label.hxx>
#include <TDF_Reference.hxx>
#include <TDF_ChildIterator.hxx>
#include <TNaming_NamedShape.hxx>
#include <TNaming_Builder.hxx>
#include <TDataStd_Real.hxx>
#include <TFunction_Logbook.hxx>
#include <TPrsStd_AISPresentation.hxx>
#include <TDataStd_Name.hxx>
#include <TFunction_DriverTable.hxx>
#include <TFunction_Function.hxx>
#include <TDataStd_Integer.hxx>

// specific IGES
#include <Interface_InterfaceModel.hxx>
#include <Interface_Static.hxx>

#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>

#include <IGESToBRep_Actor.hxx>
#include <IGESToBRep_Reader.hxx>
#include <XSControl_WorkSession.hxx>

#include <STEPControl_StepModelType.hxx>

//#include <TransferBRep_Analyzer.hxx>

// specific STL VRML
#include "StlAPI_Writer.hxx"
#include "VrmlAPI_Writer.hxx"
#include"GeomAPI_IntCS.hxx"


#include <gce_MakeLin2d.hxx>
#include <AIS_TextLabel.hxx>
#include<Prs3d_Drawer.hxx>
#include <StdPrs_Point.hxx>
#include <UnitsAPI.hxx>
//#include <AIS_InteractiveObject.hxx>
#include <PrsMgr_PresentationManager3d.hxx>
#include <Graphic3d_ArrayOfSegments.hxx>
#include <Prs3d_Arrow.hxx>
#include <ElSLib.hxx>
#include <ProjLib.hxx>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
#include <afxcview.h>
#include <afxcontrolbars.h>


#include "ISession_Point.h"

#include"ISession_Direction.h"
#include"ISession_Coordinates.h"
#include <afxwin.h>
#include <afxwin.h>
#include <afxwin.h>
#include <afxwin.h>
#include <afxwin.h>
#include <afxwin.h>




#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


