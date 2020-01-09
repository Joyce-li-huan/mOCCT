#include "stdafx.h"
#include "AIS_Text.h"
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

AIS_Text::AIS_Text()
{
}


AIS_Text::~AIS_Text()
{
}
void AIS_Text::Compute(const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
	const Handle(Prs3d_Presentation)& thePresentation,
	const Standard_Integer theMode)
{
	//Handle(Prs3d_TextAspect) anAsp = myDrawer->TextAspect();
	//gp_Pnt aTextPosition (0,0,0.);

	//Prs3d_Text::Draw(Prs3d_Root::CurrentGroup(thePresentation),anAsp,myText,aTextPosition);

	Font_BRepFont aBrepFont("C:/Windows/Fonts/arial.ttf", 3.5);
	Font_BRepTextBuilder aTextBuilder;
	TopoDS_Shape aTextShape = aTextBuilder.Perform(aBrepFont, NCollection_String("eryar@163.com"));

//	BRepTools::Dump(aTextShape, std::cout);
//	BRepTools::Write(aTextShape, "d:/text.brep");
}


void AIS_Text::SetText(TCollection_AsciiString & theText)
{
	myText = theText;
}
void AIS_Text::SetHeight(const Standard_Real theHeight)
{
	myDrawer->TextAspect()->SetHeight(theHeight);
}

void AIS_Text::ConvertToUnicode(Standard_CString aText)
{
	//TCollection_ExtendedString::ToUTF8CString(aText);

	//תunicode
	char* unicode = "";
	UINT nCodePage = 936; //GB2312
	int len = MultiByteToWideChar(nCodePage, 0, aText, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(nCodePage, 0, aText, -1, wstr, len);
	len = len * sizeof(wchar_t);
	memcpy(unicode, wstr, len);
	myText = wstr;

	
	
}
