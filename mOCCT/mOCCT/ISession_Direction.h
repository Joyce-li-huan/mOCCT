#pragma once
#include "gp_Dir2d.hxx"
class ISession_Direction;
DEFINE_STANDARD_HANDLE(ISession_Direction, AIS_InteractiveObject)
class ISession_Direction :
	public AIS_InteractiveObject
{
public:
	TCollection_ExtendedString myText;
	void SetText(TCollection_ExtendedString& aText);
	void SetText(Standard_CString aText);
	void SetLineAspect(const Handle(Prs3d_LineAspect)& theAspect);
	ISession_Direction();
	ISession_Direction(const gp_Pnt& aPnt, const gp_Dir& aDir, Standard_Real aLength = 1, Standard_Real anArrowLength = 1);
	ISession_Direction(const gp_Pnt& aPnt, const gp_Vec& aVec, Standard_Real anArrowLength = 1);

	ISession_Direction(const gp_Pnt2d& aPnt2d, const gp_Dir2d& aDir2d, Standard_Real aLength = 1);
	ISession_Direction(const gp_Pnt2d& aPnt2d, const gp_Vec2d& aVec2d);

	virtual ~ISession_Direction();
	DEFINE_STANDARD_RTTIEXT(ISession_Direction, AIS_InteractiveObject)
//	ISession_Direction();
//	~ISession_Direction();
private:

	void Compute(const Handle(PrsMgr_PresentationManager3d)& aPresentationManager,
		const Handle(Prs3d_Presentation)& aPresentation,
		const Standard_Integer aMode);
	void Compute(const Handle(Prs3d_Projector)& aProjector,
		const Handle(Prs3d_Presentation)& aPresentation);
	void ComputeSelection(const Handle(SelectMgr_Selection)& aSelection, const Standard_Integer aMode);

	gp_Pnt myPnt;
	gp_Dir myDir;
	Standard_Real myLength;
	Standard_Real myArrowLength;
};

