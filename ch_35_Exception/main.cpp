#include <stdio.h>
#include <windows.h>


INT LnDbg_BadReadPtr(void* p, int iSize);
INT LnDbg_BadWritePtr(void* p, int iSize);



class ExceptV
{
public:
	char s[2048];
public:
	ExceptV(char *format,...)
	{
		s[0] = 0;
		va_list ap;
		
		if (format == NULL)
			return;
		
		va_start(ap, format);
		vsprintf((char *)s, format, ap);
		va_end(ap);
	}
	
	void ExceptMessage()
	{
		printf("%s\n", s);
	}
};


template<class T>
class ExceptT
{
public:
	T		m;
	
public:
	ExceptT()
	{
	}
	
	void ExceptMessage()
	{
		m();
	}
};


// Fuctor를 사용하는 structure
struct ErrMsg1	{	operator()(){	printf("ErrMsg1\n");	}	};




int main()
{
	try
	{
		// Variable-Argument Lists 를 이용한 Exception
		throw ExceptV("Hello world");
		throw ExceptV("Id: %d", 10);


		// WinAPI의 IsBadReadPtr, IsBadWritePtr사용의 예
		char *p = new char[100];					// 메모리할당
		p += 200001;								// 엄한 번지로 메모리위치를 이동
		BOOL c = LnDbg_BadReadPtr(p, sizeof p);		// 읽기가 가능한 곳인지 확인
		LnDbg_BadWritePtr(p, sizeof p);				// 쓰기가 가능한 곳인지 확인



		// Functor를 이요한 Exception처리
		throw ExceptT<ErrMsg1 >();
	}

	catch(ExceptV& t)
	{
		t.ExceptMessage();
	}

	catch(ExceptT<ErrMsg1>& t)
	{
		t.ExceptMessage();
	}
	
	return 1;
}





INT LnDbg_BadReadPtr(void* p, int iSize)
{
	INT hr = IsBadReadPtr(p, sizeof p);
	
	if(hr)
	{
		throw ExceptV("Read Error");
		return -1;
	}
	
	return 0;
}


INT LnDbg_BadWritePtr(void* p, int iSize)
{
	INT hr = IsBadWritePtr(p, sizeof p);
	
	if(hr)
	{
		throw ExceptV("Write Error");
		return -1;
	}
	
	return 0;
}