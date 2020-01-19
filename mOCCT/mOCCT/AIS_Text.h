#pragma once
class TCollection_ExtendedString;
class AIS_Text :
	public AIS_InteractiveObject
{
public:
	/*AIS_Text(TCollection_ExtendedString name,const gp_Pnt pnt,
		const Standard_Real angle, const Standard_Real height,
	 TCollection_AsciiString font);*/
	AIS_Text();
	~AIS_Text();
private:
	virtual void Compute(const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
		const Handle(Prs3d_Presentation)& thePresentation,
		const Standard_Integer theMode) Standard_OVERRIDE;
	virtual void ComputeSelection(const Handle(SelectMgr_Selection)& /*aSelection*/,
		const Standard_Integer /*aMode*/) Standard_OVERRIDE { };
public:
	TCollection_AsciiString    myFont;
	TCollection_AsciiString myText;
	void SetText(Standard_CString& aText);
	void SetText(TCollection_ExtendedString& aText);
	void SetHeight(const Standard_Real theHeight);
	gp_Pnt aTextPosition;
	void SetFont();
	void SetAngle();
};

