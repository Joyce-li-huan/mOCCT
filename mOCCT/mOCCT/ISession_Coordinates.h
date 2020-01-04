#pragma once



class ISession_Coordinates :
	public AIS_InteractiveObject
{
public:
	ISession_Coordinates();
	~ISession_Coordinates();
	
	
private:
	virtual void Compute (const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
		const Handle(Prs3d_Presentation)& thePresentation,
		const Standard_Integer theMode) Standard_OVERRIDE;
	virtual void ComputeSelection(const Handle(SelectMgr_Selection)& /*aSelection*/,
		const Standard_Integer /*aMode*/) Standard_OVERRIDE { };
private:
	gp_Pnt myPoint;
protected:


	Standard_Integer myViewWndWidth;
	Standard_Integer myViewWndHeight;

	

};

