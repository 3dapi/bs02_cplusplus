#include <windows.h>
#include <stdio.h>


template <class T>
class CComPtr
{
public:
	
	T p;
	
	CComPtr()
	{
		p=NULL;
	}
	CComPtr(T lp)
	{
		if ((p = lp) != NULL)
		{
//			p->AddRef();
		}
	}
	CComPtr(const CComPtr<T>& lp)
	{
		if ((p = lp.p) != NULL)
		{
			p->AddRef();
		}
	}
	~CComPtr()
	{
		if (p)
			p->Release();
	}
	void Release()
	{
		IUnknown* pTemp = p;
		if (pTemp)
		{
			p = NULL;
			pTemp->Release();
		}
	}
	
	operator T*() const
	{
		return (T*)p;
	}
	
	T& operator*() const
	{
		ATLASSERT(p!=NULL);
		return *p;
	}
	
	T** operator&()
	{
		ATLASSERT(p==NULL);
		return &p;
	}
	
	
};


struct IrrMtl
{
	DWORD Ambient;
	DWORD Diffuse;
	DWORD Specular;
	DWORD Emissive;
	FLOAT Power;
	
	
	IrrMtl()
		: Ambient(255,255,255,255)
		, Diffuse(255,255,255,255)
		, Specular(255,255,255,255)
		, Emissive(0,0,0,0)
		, Power(0.0f)
	{
	}

	INT Release()
	{
		return 1;
	}

	
};


void main( void )
{
	CComPtr<IrrMtl* >	t;
}
