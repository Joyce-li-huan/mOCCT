#pragma once
#include"mOCCTDoc.h"

#include <Aspect_Drawable.hxx>
#include <Aspect_RenderingContext.hxx>
class GeoSource
{
	
public:
	GeoSource();
	~GeoSource();
	
	Standard_EXPORT static void gpTest1(CmOCCTDoc* aDoc);
	Standard_EXPORT static void gpTest2(CmOCCTDoc* aDoc);
	Standard_EXPORT     void SetViewport(const Standard_Integer Width, const Standard_Integer Height);
	Standard_EXPORT     void TextSize(const Standard_CString AText, const Standard_Real AHeight, Standard_Real& AWidth, Standard_Real& AnAscent, Standard_Real& ADescent) const;
	Standard_EXPORT     void SetColor(const Quantity_Color& AColor);
	Standard_EXPORT     void DrawText(const Standard_CString AText, const Standard_Real X, const Standard_Real Y, const Standard_Real AHeight);


private:
	Handle_Graphic3d_GraphicDriver MyGraphicDriver;

	static void DisplayPoint(CmOCCTDoc* aDoc,
		const gp_Pnt& aPoint,
		const char* aText,
		Standard_Boolean UpdateViewer = Standard_False,
		Standard_Real anXoffset = 0,
		Standard_Real anYoffset = 0,
		Standard_Real aZoffset = 0,
		Standard_Real TextScale = 0.05);


	enum DisplayType
	{
		No2DNo3D,No2D3D,a2DNo3D,a2D3D
	};
	static  void PreProcess(CmOCCTDoc* aDoc, DisplayType aDisplayType);
};

