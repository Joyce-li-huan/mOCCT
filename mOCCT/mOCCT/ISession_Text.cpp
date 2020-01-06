#include "stdafx.h"
#include "ISession_Text.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif
IMPLEMENT_STANDARD_HANDLE(ISession_Text, AIS_InteractiveObject)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ISession_Text::ISession_Text()
{

}

ISession_Text::ISession_Text(const TCollection_AsciiString& aText)      // = 1
	:AIS_InteractiveObject(),MyText(aText),MyHeight(500),MyWidth(500)
{
	
	 
}

ISession_Text::~ISession_Text()
{

}

void ISession_Text::Compute(const Handle(PrsMgr_PresentationManager3d)& /*aPresentationManager*/,
	const Handle(Prs3d_Presentation)& aPresentation,
	const Standard_Integer /*aMode*/)
{
	Handle(Graphic3d_Group) aGroup = Prs3d_Root::CurrentGroup(aPresentation);
	aGroup->SetGroupPrimitivesAspect(myDrawer->TextAspect()->Aspect());
	aGroup->Text(MyText, Graphic3d_Vertex(0.,0.,0.), 300);

	//Prs3d_Text::Draw(aPresentation, myDrawer, MyText, gp_Pnt(MyX, MyY, MyZ));


}

void ISession_Text::Compute(const Handle(Prs3d_Projector)& /*aProjector*/,
	const Handle(Prs3d_Presentation)& /*aPresentation*/)
{
}

void ISession_Text::ComputeSelection(const Handle(SelectMgr_Selection)& /*aSelection*/,
	const Standard_Integer /*unMode*/)
{
}

