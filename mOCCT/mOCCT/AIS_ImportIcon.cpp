#include "stdafx.h"
#include "AIS_ImportIcon.h"
#include <Graphic3d_Texture2Dmanual.hxx>

AIS_ImportIcon::AIS_ImportIcon(TCollection_AsciiString& aFileName,
	const Standard_Real X,
	const Standard_Real Y,
	const Standard_Real aScale)
	:AIS_Shape(TopoDS_Shape())
{
	myFilename = aFileName;

}
void AIS_ImportIcon::MakeShape()
{
	Handle(Graphic3d_Texture1D) anImageTexture =
		new Graphic3d_Texture1Dsegment(myFilename);
	Standard_Real coeff = (Standard_Real)(anImageTexture->GetImage()->Height()) /
		(anImageTexture->GetImage()->Width())*2;
	TopoDS_Edge E1 = BRepBuilderAPI_MakeEdge(gp_Pnt(0, 0, 0.), gp_Pnt(100 * 2 + 0, 0, 0.));
	TopoDS_Edge E2 = BRepBuilderAPI_MakeEdge(gp_Pnt(100 * 2 + 0, 0, 0.), gp_Pnt(100 * 2 + 0, 100 * 1 + 0, 0.));
	TopoDS_Edge E3 = BRepBuilderAPI_MakeEdge(gp_Pnt(100 * 2 + 0, 100 * 1 + 0, 0.), gp_Pnt(0, 100 * 1 + 0, 0.));
	TopoDS_Edge E4 = BRepBuilderAPI_MakeEdge(gp_Pnt(0, 100 * 1 + 0, 0.), gp_Pnt(0, 0, 0.));
	TopoDS_Wire anImageBounds = BRepBuilderAPI_MakeWire(E1, E2, E3, E4);
	myFace = BRepBuilderAPI_MakeFace(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), anImageBounds);
}
void AIS_ImportIcon::SetContext(const Handle(AIS_InteractiveContext)& theContext)
{
	if (theContext.IsNull() || theContext->CurrentViewer().IsNull()) return;
	AIS_InteractiveObject::SetContext(theContext);
	MakeShape();
	this->Set(TopoDS_Shape(myFace));
	myDrawer->SetShadingAspect(new Prs3d_ShadingAspect());
	Handle(Graphic3d_Texture2Dmanual) aTexture = new Graphic3d_Texture2Dmanual(myFilename);
	aTexture->DisableModulate();
	myDrawer->ShadingAspect()->Aspect()->SetTextureMap(aTexture);
	myDrawer->ShadingAspect()->Aspect()->SetTextureMapOn();
}
