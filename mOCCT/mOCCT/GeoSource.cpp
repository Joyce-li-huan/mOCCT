#include "stdafx.h"
#include "GeoSource.h"



GeoSource::GeoSource()
{
}


GeoSource::~GeoSource()
{
}


void GeoSource::gpTest1(CmOCCTDoc* aDoc)
{
	//DisplayType TheDisplayType = No2D3D;
	//PreProcess(aDoc,TheDisplayType);
	gp_Pnt p1(10, 20, 30);
	DisplayPoint(aDoc,p1,"点(1,2,3)",false,30);

}
void GeoSource::gpTest2(CmOCCTDoc* aDoc)
{	gp_Pnt p1(1, 2, 3);
	gp_Pnt p2(5,4,6);
	gp_Vec V1(p1,p2);

	DisplayPoint(aDoc, p2, "点P2", false, 0.5);
	Handle(ISession_Direction) aDirection1 = new ISession_Direction(p1, V1);
	aDoc->GetAISContext()->Display(aDirection1, Standard_False);
}
void GeoSource::PreProcess(CmOCCTDoc* aDoc, DisplayType aDisplayType)
{
	if (aDisplayType == No2D3D)
	{
		aDoc->GetAISContext()->EraseAll(Standard_True);
		aDoc->Put3DOnTop();
	}
}

//	DisplayPoint(aDoc,p1,"p1(1,2,3)",false,30);
void GeoSource::DisplayPoint(CmOCCTDoc* theDoc,
	const gp_Pnt& thePoint,
	const char* theText,
	Standard_Boolean theToUpdateViewer,
	Standard_Real theXoffset,
	Standard_Real theYoffset,
	Standard_Real theZoffset,
	Standard_Real theTextScale)
{

	Handle(ISession_Point) aGraphicPoint = new ISession_Point(thePoint);
	theDoc->GetAISContext()->Display(aGraphicPoint, Standard_False);

	Handle(AIS_TextLabel) aLabel = new AIS_TextLabel();


	
	//char* unicode = "";
	//	UINT nCodePage = 936; //GB2312
	//	int len = MultiByteToWideChar(nCodePage, 0, theText, -1, NULL, 0);
	//	wchar_t* wstr = new wchar_t[len + 1];
	//	memset(wstr, 0, len + 1);
	//	MultiByteToWideChar(nCodePage, 0, theText, -1, wstr, len);
	//	len = len * sizeof(wchar_t);
	//	memcpy(unicode, wstr, len);


	aLabel->SetText(theText);
	//aLabel->SetContext(theText);
	aLabel->SetPosition(gp_Pnt(110, 60, thePoint.Z() + theZoffset));
	aLabel->SetHeight (theTextScale);
	aLabel->SetAngle(0);
	aLabel->SetZoomable(false);
	aLabel->SetFont("中文");

	aLabel->SetFontAspect(Font_FA_Undefined);
	//aLabel->SetAspect();
	
	(void)theTextScale;
	theDoc->GetAISContext()->Display(aLabel, theToUpdateViewer);
}
void GeoSource::SetViewport(const Standard_Integer Width, const Standard_Integer Height) {
#ifdef TRACE_CALL
	cout << "Visual3d_Layer::SetViewport" << endl;
#endif


}
void GeoSource::TextSize(const Standard_CString AText, const Standard_Real AHeight, Standard_Real& AWidth, Standard_Real& AnAscent, Standard_Real& ADescent) const {
	Standard_ShortReal aWidth, anAscent, aDescent;

#ifdef TRACE_CALL
	cout << "Visual3d_Layer::TextSize" << endl;
#endif
	//if (!theLayerState)
	//	Visual3d_LayerDefinitionError::Raise
	//	("Layer is not open !");
	//if (theTypeOfPrimitive != Graphic3d_TOP_UNDEFINED)
	//	Visual3d_LayerDefinitionError::Raise
	//	("One primitive is already open !");

	//MyGraphicDriver->TextSize(AText, AHeight, aWidth, anAscent, aDescent);
//	AWidth = aWidth;
//	AnAscent = anAscent;
//	ADescent = aDescent;
}
void GeoSource::SetColor(const Quantity_Color& AColor) {
#ifdef TRACE_CALL
	cout << "Visual3d_Layer::SetColor" << endl;
#endif
	//if (!theLayerState)
	//	Visual3d_LayerDefinitionError::Raise
	//	("Layer is not open !");

	Standard_ShortReal r = Standard_ShortReal(AColor.Red());
	Standard_ShortReal g = Standard_ShortReal(AColor.Green());
	Standard_ShortReal b = Standard_ShortReal(AColor.Blue());
#ifdef TRACE_CALL
	cout << "\tSetColor : " << r << ", " << g << ", " << b << endl;
#endif
	/*MyGraphicDriver->SetColor(r, g, b);*/
}

void GeoSource::DrawText(const Standard_CString AText, const Standard_Real X, const Standard_Real Y, const Standard_Real AHeight) {
#ifdef TRACE_CALL
	cout << "Visual3d_Layer::DrawText" << endl;
#endif
	//if (!theLayerState)
	//	Visual3d_LayerDefinitionError::Raise
	//	("Layer is not open !");
	//if (theTypeOfPrimitive != Graphic3d_TOP_UNDEFINED)
	//	Visual3d_LayerDefinitionError::Raise
	//	("One primitive is already open !");

	//Standard_ShortReal x = Standard_ShortReal(X);
	//Standard_ShortReal y = Standard_ShortReal(Y);
	//Standard_ShortReal height = Standard_ShortReal(AHeight);
	//MyGraphicDriver->Text(AText, x, y, height);
}