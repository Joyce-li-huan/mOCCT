#pragma once
class AIS_ImportIcon :
	public AIS_Shape
{
public:
	Standard_EXPORT AIS_ImportIcon(TCollection_AsciiString& ImportIcon,
		const Standard_Real X = 0.0,
		const Standard_Real Y = 0.0,
		const Standard_Real aScale = 1.0);
	Standard_EXPORT virtual void SetContext(const Handle(AIS_InteractiveContext)& theContext);
private:
	void MakeShape();
protected:
	TopoDS_Face myFace;
	TCollection_AsciiString ImageIcon;
};

