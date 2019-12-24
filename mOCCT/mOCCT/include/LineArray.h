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
		// ���·���һ���ڴ棬���СΪ�����T��������Ĵ�С
		m_pData = (string*) realloc(m_pData, sizeof(TYPE) * iSize); 
		// �����󲿷ֵ��ڴ�ռ��Ͻ���T���͵�������󣬲�������Ĭ�Ϲ��캯��
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
		//����ĳ�ʼ��С��1��T���Ͷ���
		//����һ���ڴ����СΪT������ռ�Ŀռ�
		m_bCanDelete = 0;
		m_pData = (TYPE*)malloc(sizeof(TYPE));
		//���ڴ�ռ��н���һ��T�Ͷ���

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
		// ����±��Ǹ�ֵ���׳�һ���쳣

		if( index < 0 ) throw std::out_of_range(" Index shouldn''t be negative"); 

		//����±��Ƿ��������С��������������EnlargeDim��������

		if(index > m_iSize - 1)
		 EnlargeDim(index + 1);
		return m_pData [index];
	};
	
};

