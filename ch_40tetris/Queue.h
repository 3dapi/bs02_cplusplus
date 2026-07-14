// Que.h: interface for the CQue class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _QUE_H_
#define _QUE_H_

////
// Front 뒤는 항상 비워둔다.

template<class T>
class CQueue
{
protected:
	//int m_Que[_QUE_MAX_SIZE];
	T *m_Que;
	int m_nSize;
	int m_nFront;
	int m_nReal;
public:
	//
	CQueue()
	{
		m_nSize = m_nFront = m_nReal = 0;
		m_Que = NULL;
	};
	virtual ~CQueue()
	{
		Destroy();
	};

	//
	enum {
		CRITIACAL_SPACE	=	1,
		EMPTY_SPACE		=	0x0
	};

	//
	int Init(int nSize=1024000);
	void Destroy()
	{
			delete []m_Que;
	};

	//
	int Put(T* nData);
	int Get(T* nData);

	//
	int Puts(T* nData, int nSize);
	int Gets(T* nData, int nSize);

	//
	int GetNFree()
	{
		return ((m_nFront<=m_nReal)? m_nSize-(m_nReal-m_nFront): m_nSize-(m_nSize-m_nFront)-m_nReal)-CRITIACAL_SPACE;
	}
	int GetNData()
	{
		return (m_nFront<=m_nReal)? m_nReal-m_nFront: (m_nSize-m_nFront)+m_nReal;
	}

	//
	void ShowQue()
	{
	#ifdef _DEBUG
		printf("\t");
		for(int i=0;i<m_nSize;++i)
		{
			printf("[%c] ", m_Que[i]);
		}
		printf("\n\tFront : %d, Real : %d\n", m_nFront, m_nReal);
	#endif
	}
};

template <class T>
int CQueue<T>::Init(int nSize/* =10 */)
{
	m_Que = new T [nSize];
	if(m_Que == NULL)
	{
		return 0;
	}

	m_nSize = nSize;

	memset(m_Que, EMPTY_SPACE, sizeof(T)*nSize);

	return 1;
}

template<class T>
int CQueue<T>::Puts(T* nData, int nSize)
{
	int nFree = GetNFree();
	if (nSize > GetNFree()) return -1;

	if ( (m_nSize-m_nReal) > nSize )
	{
		memcpy(m_Que+m_nReal, nData, sizeof(T)*nSize);
		m_nReal=(m_nReal+nSize)%m_nSize;
	}
	else
	{
		int nOutSize = m_nSize - m_nReal;
		
		memcpy(m_Que+m_nReal, nData, sizeof(T)*nOutSize);
		m_nReal=(m_nReal+nOutSize)%m_nSize;

		memcpy(m_Que+m_nReal, nData+nOutSize, sizeof(T)*(nSize-nOutSize));
		m_nReal=(m_nReal+(nSize-nOutSize))%m_nSize;
	}

	return 1;
}

template<class T>
int CQueue<T>::Gets(T* nData, int nSize)
{
	if( nSize > GetNData() ) return -1;

	if( m_nSize > m_nFront + nSize )
	{
		memcpy(nData, m_Que+m_nFront, sizeof(T)*nSize);
		memset(m_Que+m_nFront, EMPTY_SPACE, sizeof(T)*nSize);
		m_nFront=(m_nFront+nSize)%m_nSize;
	}
	else
	{
		int nOutSize = m_nSize - m_nFront;
		memcpy(nData, m_Que+m_nFront, sizeof(T)*nOutSize);
		memset(m_Que+m_nFront, EMPTY_SPACE, sizeof(T)*nOutSize);
		m_nFront=(m_nFront+nOutSize)%m_nSize;

		memcpy(nData+nOutSize, m_Que+m_nFront, sizeof(T)*(nSize - nOutSize));
		memset(m_Que+m_nFront, EMPTY_SPACE, sizeof(T)*nSize-nOutSize);
		m_nFront=(m_nFront+(nSize-nOutSize))%m_nSize;
	}

	return 1;
}

template<class T>
int CQueue<T>::Get(T* nData)
{
	if(m_nFront == m_nReal) return -1;
	*nData = m_Que[m_nFront];

	m_Que[m_nFront]=EMPTY_SPACE;

	m_nFront = (m_nFront+1)%m_nSize;

	return 1;
}

template<class T>
int CQueue<T>::Put(T* nData)
{
	if ((m_nReal+1)%m_nSize == m_nFront) return -1;
	m_Que[m_nReal] = *nData;

	m_nReal = (m_nReal+1)%m_nSize;

	return 1;
}

#endif