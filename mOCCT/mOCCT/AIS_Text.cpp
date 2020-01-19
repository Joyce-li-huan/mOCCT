#include "stdafx.h"
#include "AIS_Text.h"
#include <BRepTools.hxx>

#include <Font_BRepFont.hxx>
#include <Font_BRepTextBuilder.hxx>
#include<Resource_Unicode.hxx>

//AIS_Text::AIS_Text(TCollection_ExtendedString name, const gp_Pnt pnt,
//	const Standard_Real angle,  const Standard_Real height, TCollection_AsciiString font)
AIS_Text::AIS_Text()
	:myFont("SimHei")
{
	//aTextPosition = pnt;
	//myText = name;
	
	myDrawer->SetTextAspect(new Prs3d_TextAspect());
}
AIS_Text::~AIS_Text()
{
}
void AIS_Text::Compute(const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
	const Handle(Prs3d_Presentation)& thePresentation,
	const Standard_Integer theMode)
{
	Handle(Prs3d_TextAspect) anAsp = myDrawer->TextAspect();

	Prs3d_Text::Draw(Prs3d_Root::CurrentGroup(thePresentation),anAsp,myText,aTextPosition);

}

void AIS_Text::SetText(TCollection_ExtendedString & theText)
{
	myText = theText;
}
void AIS_Text::SetText(Standard_CString & theText)
{
	myText = theText;
}
void AIS_Text::SetHeight(const Standard_Real theHeight)
{
	myDrawer->TextAspect()->SetHeight(theHeight);
}

void AIS_Text::SetFont()
{
	myDrawer->TextAspect()->SetFont(myFont.ToCString());
}


void AIS_Text::SetAngle()
{
	myDrawer->TextAspect()->Aspect()->SetTextAngle(0);
}
