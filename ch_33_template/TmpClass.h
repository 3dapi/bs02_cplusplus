// Interface for the CTmpClass class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _TMPCLASS_H_
#define _TMPCLASS_H_

class CAdderInt
{
private:
	INT	m_iSum;

public:
	CAdderInt()
		:	m_iSum	(0)
	{
	}

	void Add(INT iNumber)
	{
		m_iSum += iNumber;
	}

	INT	Sum()
	{
		return m_iSum;
	}

};

class CAdderFloat
{
private:
	FLOAT	m_fSum;

public:
	CAdderFloat()
		:	m_fSum	(0)
	{
	}

	void Add(FLOAT fNumber)
	{
		m_fSum += fNumber;
	}

	FLOAT	Sum()
	{
		return m_fSum;
	}
};


template<class T>
class CAdderT
{
private:
	T	m_Sum;

public:
	CAdderT()
		:	m_Sum	(0)
	{
	}

	void Add(T (Number))
	{
		m_Sum += Number;
	}

	T	Sum()
	{
		return m_Sum;
	}
};




template<class T1, class T2, class T3, T1 value1, T3 value2, int iT1Size=5, INT iT2Size=15, INT iT3Size = 25>
class CTmpMulti
{
public:
	T1	t1[iT1Size];
	T2	t2[iT2Size];
	T3	t3[iT3Size];

public:
	CTmpMulti()
	{
	}

	T1	GetT1(INT nI)
	{
		return t1[nI];
	}

	T2	GetT2(INT nI)
	{
		return t2[nI];
	}

	T3	GetT3(INT nI)
	{
		return t3[nI];
	}
	
};




class ClassA
{
public:
	int a;

	ClassA() : a(1){}

	int Init()
	{
		printf("Init class A, %d\n", a);

		return 1;
	}
};


class ClassB
{
public:
	int b;

	ClassB() : b(2){}

	int Init()
	{
		printf("Init class B, %d\n", b);

		return 1;
	}
};


class ClassC
{
public:
	int c;

	ClassC() : c(3){}

	int Init()
	{
		printf("Init class C, %d\n", c);

		return 1;
	}
};


template<typename T>
int NewInit(T* &p)
{
	if(NULL == p || (void*)p == (void*)0xCCCCCCCC || (void*)p==(void*)0xCDCDCDCD)
	{
		p = new T;
	}
	

	return p->Init();
}


template<typename T>
void Delete(T* &p)
{
	if(NULL != p && (void*)p != (void*)0xCCCCCCCC && (void*)p != (void*)0xCDCDCDCD)
	{
		delete p;
		p = NULL;
	}
}


#endif _TMPCLASS_H_
