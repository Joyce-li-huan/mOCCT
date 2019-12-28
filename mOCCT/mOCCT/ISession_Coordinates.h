#pragma once

#include <Graphic3d_ArrayOfPolylines.hxx>

DEFINE_STANDARD_HANDLE(ISession_Coordinates, AIS_InteractiveObject)
class ISession_Coordinates :
	public AIS_InteractiveObject
{
public:
	ISession_Coordinates();
	~ISession_Coordinates();
	ISession_Coordinates(const Quantity_Color& theLineColor,
						const Aspect_TypeOfLine theType,
						const Quantity_Color theFillColor,
						const Standard_Real theTransparency ,
						const Standard_Real theLineWidth ,
						const Standard_Boolean theIsPolygonClosed );
	
private:
	void Compute (const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
		const Handle(Prs3d_Presentation)& thePresentation,
		const Standard_Integer /*theMode*/) Standard_OVERRIDE;

	void ComputeSelection(const Handle(SelectMgr_Selection)& /*aSelection*/,
		const Standard_Integer /*aMode*/);

private:
	gp_Pnt myPoint;

};

