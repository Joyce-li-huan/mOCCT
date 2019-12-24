// LineArray.h: interface for the CLineArray class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include"GMath.h"
template<class TYPE>
class GMATH_API CLineArray
{
protected:
	TYPE *m_pData;
	bool m_bCanDelete;
protected:
    bool GMATH_API EnlargeDim(int iSize)
	{
		// 重新分配一块内存，其大小为扩大后T类型数组的大小
		m_pData = (string*) realloc(m_pData, sizeof(TYPE) * iSize); 
		// 在扩大部分的内存空间上建立T类型的数组对象，并调用其默认构造函数
		for(int i = m_iSize; i < iSize; i++)
		{
		 new(&m_pData[i]) TYPE();
		}
		m_iSize = iSize;
		return true;
	}

public:
	//Construction
	GMATH_API CLineArray()
	{
		//数组的初始大小的1个T类型对象
		//分配一块内存其大小为T型类所占的空间
		m_bCanDelete = 0;
		m_pData = (TYPE*)malloc(sizeof(TYPE));
		//在内存空间中建立一个T型对象

		new(m_pData) TYPE(); 
		m_iSize = 1;
	};
	
	GMATH_API virtual ~CLineArray()
	{
	
	};
	//Attribute
	int    m_iSize;
	void GMATH_API SetCanDelete(bool bCanDelete = false)
	{
		m_bCanDelete = bCanDelete;
	};

	GMATH_API TYPE *GetData()
	{
		return m_pData;
	}

	GMATH_API TYPE operator[](int nIndex) const
	{
		return &m_pData[i];
	};

	GMATH_API TYPE& operator[](int index)
	{
		// 如果下标是负值，抛出一个异常

		if( index < 0 ) throw std::out_of_range(" Index shouldn''t be negative"); 

		//检查下标是否超来数组大小，如果超过则调用EnlargeDim扩大数组

		if(index > m_iSize - 1)
		 EnlargeDim(index + 1);
		return m_pData [index];
	};
	
};

