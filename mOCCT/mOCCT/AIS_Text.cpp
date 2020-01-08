#include "stdafx.h"
#include "AIS_Text.h"


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
	Handle(Prs3d_TextAspect) anAsp = myDrawer->TextAspect();
	gp_Pnt aTextPosition (0,0,0.);

	Prs3d_Text::Draw(Prs3d_Root::CurrentGroup(thePresentation),anAsp,myText,aTextPosition);
}


void AIS_Text::SetText(Standard_CString & theText)
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
