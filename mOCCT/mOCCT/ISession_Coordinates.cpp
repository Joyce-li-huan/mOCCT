#include "stdafx.h"
#include "ISession_Coordinates.h"

#include <Graphic3d_ArrayOfPolygons.hxx>


ISession_Coordinates::ISession_Coordinates()
{
	SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_2d,Aspect_TOTP_LEFT_LOWER));
	SetZLayer(Graphic3d_ZLayerId_TopOSD);
}


ISession_Coordinates::~ISession_Coordinates()
{
}


void ISession_Coordinates:: Compute(const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
									const Handle(Prs3d_Presentation)& thePresentation,
									const Standard_Integer theMode)
{

	Handle(Graphic3d_Group) aGroup = Prs3d_Root::CurrentGroup(thePresentation);

	Handle(Graphic3d_AspectLine3d) aLineAspect =
		new Graphic3d_AspectLine3d(Quantity_Color(0.4, 0.43, 0.43, Quantity_TOC_RGB), Aspect_TOL_SOLID, 2);
	Handle(Graphic3d_AspectText3d) aTextAspect =
		new Graphic3d_AspectText3d(Quantity_Color(0.2, 0.2, 0.2, Quantity_TOC_RGB),
			"Arial", 1, 5);
	aGroup->SetGroupPrimitivesAspect(aLineAspect);
	aGroup->SetGroupPrimitivesAspect(aTextAspect);

	
	Handle(Graphic3d_ArrayOfPolylines) myGridCell = new Graphic3d_ArrayOfPolylines(5);

	myGridCell->AddVertex(100, 100, 0.0);
	myGridCell->AddVertex(100, 200, 0.0);
	myGridCell->AddVertex(200, 100, 0.0);
	myGridCell->AddVertex(200, 200, 0.0);
	aGroup->AddPrimitiveArray(myGridCell);

	aGroup->Text("X", Graphic3d_Vertex(100,100, 0.0), 50);

}




//int x1 = 0;
//int y1 = 659;
//int x2 = 25;
//int y2 = 674;
//int x3 = 50;
//int y3 = 659;
//int x4 = 25;
//int y4 = 645;
//TopoDS_Face BlueFace;
//TopoDS_Edge E11 = BRepBuilderAPI_MakeEdge(gp_Pnt(x1, y1, 0), gp_Pnt(x2, y2, 0));
//TopoDS_Edge E12 = BRepBuilderAPI_MakeEdge(gp_Pnt(x2, y2, 0), gp_Pnt(x3, y3, 0));
//TopoDS_Edge E13 = BRepBuilderAPI_MakeEdge(gp_Pnt(x3, y3, 0), gp_Pnt(x4, y4, 0));
//TopoDS_Edge E14 = BRepBuilderAPI_MakeEdge(gp_Pnt(x4, y4, 0), gp_Pnt(x1, y1, 0));
//BRepBuilderAPI_MakeWire W1(E11, E12, E13, E14);
//BlueFace = BRepBuilderAPI_MakeFace(W1);
//Handle(AIS_InteractiveContext) myAISContext;
//Handle(AIS_Shape) Blue = new AIS_Shape(BlueFace);
//myAISContext->SetColor(Blue, Quantity_NOC_BLACK, Standard_False);
//myAISContext->SetMaterial(Blue, Graphic3d_NOM_PLASTIC, Standard_False);
//
//StdPrs_ShadedShape::Add(thePrs, W1, myDrawer);