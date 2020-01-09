#pragma once
class TCollection_ExtendedString;
class AIS_Text :
	public AIS_InteractiveObject
{
public:
	AIS_Text();
	~AIS_Text();
private:
	virtual void Compute(const Handle(PrsMgr_PresentationManager3d)& thePresentationManager,
		const Handle(Prs3d_Presentation)& thePresentation,
		const Standard_Integer theMode) Standard_OVERRIDE;
	virtual void ComputeSelection(const Handle(SelectMgr_Selection)& /*aSelection*/,
		const Standard_Integer /*aMode*/) Standard_OVERRIDE { };
public:
	TCollection_ExtendedString myText;
	void SetText(TCollection_AsciiString& aText);
	void ConvertToUnicode(Standard_CString aText);
	void SetHeight(const Standard_Real theHeight);
};

