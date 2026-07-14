// Que.cpp: implementation of the CQue class.
//
//////////////////////////////////////////////////////////////////////

#include "_stdafx.h"
/*
template<class T>
CQueue<T>::CQueue()
{
	m_nSize = m_nFront = m_nReal = 0;
	
	m_Que = NULL;
}

template<class T>
CQueue<T>::~CQueue()
{
	Destroy();
}

template <class T>
int CQueue<T>::Init(int nSize)
{
	m_Que = new T [nSize];
	m_nSize = nSize;
	for(int i=0;i<m_nSize;++i)
	{
		m_Que[i] = -1;
	}

	return 1;
}

template<class T>
void CQueue<T>::Destroy()
{
	delete []m_Que;
}

template<class T>
bool CQueue<T>::Get(T* nNum)
{
	if(m_nFront == m_nReal) return false;
	*nNum = m_Que[m_nFront];

	m_Que[m_nFront]=-1;

	m_nFront = (m_nFront+1)%m_nSize;

	return true;
}

template<class T>
bool CQueue<T>::Put(T* nNum)
{
	if ((m_nReal+1)%m_nSize == m_nFront)
		return false;
	m_Que[m_nReal] = *nNum;

	m_nReal = (m_nReal+1)%m_nSize;

	return true;
}

template<class T>
void CQueue<T>::ShowQue()
{
#ifdef _DEBUG
	printf("\t");
	for(int i=0;i<m_nSize;++i)
	{
		printf("[%d] ", m_Que[i]);
	}
	printf("\n\tFront : %d, Real : %d\n", m_nFront, m_nReal);
#endif
}
*/