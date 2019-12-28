#include "stdafx.h"
#include "ISession_Coordinates.h"



ISession_Coordinates::ISession_Coordinates()
{
}

ISession_Coordinates::~ISession_Coordinates()
{
}

//显示
ISession_Coordinates::ISession_Coordinates(const Quantity_Color& theLineColor,
											const Aspect_TypeOfLine theLineType,
											const Quantity_Color theFillColor,
											const Standard_Real theTransparency = 1.0,
											const Standard_Real theLineWidth = 1.0,
											const Standard_Boolean theIsPolygonClosed = Standard_True)
{

		myDrawer->SetLineAspect(new Prs3d_LineAspect(theLineColor, theLineType, theLineWidth));
		myDrawer->SetShadingAspect(new Prs3d_ShadingAspect());
		myDrawer->ShadingAspect()->SetMaterial(Graphic3d_NOM_PLASTIC);
		myDrawer->ShadingAspect()->SetColor(theFillColor);
		myDrawer->ShadingAspect()->Aspect()->SetInteriorStyle(Aspect_IS_SOLID);
		myDrawer->ShadingAspect()->Aspect()->SetAlphaMode(Graphic3d_AlphaMode_Blend);
		myDrawer->ShadingAspect()->SetTransparency(theTransparency);


		SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_2d,  Aspect_TOTP_RIGHT_UPPER ));
		SetZLayer(Graphic3d_ZLayerId_TopOSD);
}

void ISession_Coordinates:: Compute(const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
									const Handle(Prs3d_Presentation)& thePresentation,
									const Standard_Integer /*theMode*/)
{
	// 得到组
	Handle(Graphic3d_Group) aGroup = thePresentation->NewGroup();
	
	// 改变文字属性
	Handle(Graphic3d_AspectText3d) aTextAspect = new Graphic3d_AspectText3d();
	aTextAspect->SetTextZoomable(false);
	aTextAspect->SetTextAngle(0.0);
	aTextAspect->SetColor(Quantity_NOC_BLUE1);
	aGroup->SetPrimitivesAspect(aTextAspect);
	// 把文字添加到结构中
	Graphic3d_Vertex aPoint(0, 500, 100.);
	aGroup->Text(Standard_CString("X"), aPoint, 16.0);

	
	
	//画矩形
	// create an array
	Standard_Boolean hasNormals = false;
	Standard_Boolean hasColors = false;
	Standard_Boolean hasTextureCrds = false;
//	Handle(Graphic3d_ArrayOfTriangles) anArray = new Graphic3d_ArrayOfTriangles(theVerticesMaxCount, theEdgesMaxCount, hasNormals, hasColors, hasTextureCrds);
	// add vertices to the array
	//anArray->AddVertex(-1.0, 0.0, 0.0); // vertex 1
	//anArray->AddVertex(1.0, 0.0, 0.0); // vertex 2
	//anArray->AddVertex(0.0, 1.0, 0.0); // vertex 3
	//anArray->AddVertex(0.0, -1.0, 0.0); // vertex 4
	//// add edges to the array
	//anArray->AddEdge(1);  // first triangle
	//anArray->AddEdge(2);
	//anArray->AddEdge(3);
	//anArray->AddEdge(1);  // second triangle
	//anArray->AddEdge(2);
	//anArray->AddEdge(4);
	//// add the array to the structure
	//Handle(Graphic3d_Group) aGroup = thePrs->NewGroup();
	//aGroup->AddPrimitiveArray(anArray);
	//aGroup->SetGroupPrimitivesAspect(myDrawer->ShadingAspect()->Aspect());
}



void ISession_Coordinates::ComputeSelection(const Handle(SelectMgr_Selection)& /*aSelection*/,
	const Standard_Integer /*unMode*/)
{

}




	// 画文字
	/*TCollection_ExtendedString myText = "X:";
	gp_Pnt aTextPosition (0,500,300);
	Prs3d_Text::Draw(Prs3d_Root::CurrentGroup(thePresentation), myDrawer->TextAspect(), myText, aTextPosition);

	Standard_CString myTexty = "Y:";
	gp_Pnt aTextPositiony(0, 500, 250);
	Prs3d_Text::Draw(Prs3d_Root::CurrentGroup(thePresentation), myDrawer->TextAspect(), myTexty, aTextPositiony);

	Standard_CString myTextz = "Z:";
	gp_Pnt aTextPositionz(0, 500, 200);
	Prs3d_Text::Draw(Prs3d_Root::CurrentGroup(thePresentation), myDrawer->TextAspect(), myTextz, aTextPositionz);
	
	
	Handle(AIS_TextLabel) aLabel = new AIS_TextLabel();
	aLabel->SetText(myText);
	aLabel->SetPosition(gp_Pnt(0,0,0));
	aLabel->SetHeight(20);
	aLabel->SetAngle(0);
	aLabel->SetZoomable(false);*/
	
	
	


