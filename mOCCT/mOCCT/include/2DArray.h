// 2DArray.h: interface for the C2DArray class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include"linearray.h"
#include"GMath.h"

template<class TYPE>
class GMATH_API C2DArray:public CLineArray<TYPE>
{
	int m_nD2;
	int m_nD1;
public:

	GMATH_API C2DArray(bool bCanDelete = false,TYPE *pData = NULL,int D2 =0,int D1=0)
	{
		m_bCanDelete = bCanDelete;
		m_pData = pData;

		m_nD1 = D1;

		m_nD2 = D2;
		if(!m_pData)
		{
			m_pData = new TYPE[D2*D1];
		}
	};


	void GMATH_API RemoveAll()
	{
		m_nD2 = 0;
		m_nD1 = 0;
		delete []m_pData;
		m_pData = NULL;
	};

	//##ModelId=42C3BACA0271
	int GMATH_API GetD1()
	{
		return m_nD1;
	};
	//##ModelId=42C3BACA0272
	int GMATH_API GetD2()
	{
		return m_nD2;
	};
	//##ModelId=42C3BACA0273
	void GMATH_API SetDimLen(int D2,int D1,bool bCanDelete = true)
	{
		m_nD2 = D2;
		m_nD1 = D1;

		m_pData = new TYPE[D1*D2];
		m_bCanDelete = bCanDelete; 
	};

	//##ModelId=42C3BACA0282
	GMATH_API TYPE * operator[](int i)
	{
		return &m_pData[i*m_nD1];
	}

};

