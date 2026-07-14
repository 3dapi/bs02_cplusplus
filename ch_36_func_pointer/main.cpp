////////////////////////////////////////////////////////////////////////////////
// 
// Explain: 함수 포인터

#include <stdio.h>
#include <memory.h>


int TestFunc1(char* sParam)
{
	return printf("TestFunc1:%s\n", sParam);
}


int TestFunc2(char* sParam)
{
	return printf("TestFunc2:%s\n", sParam);
}

int TestFunc3(char* sParam)
{
	return printf("TestFunc3:%s\n", sParam);
}


class CTest1
{
private:
	//	int	 (CTest1::*OnFuncPtr	[4])(char*);									// Game phase frame move function pointer
	int (CTest1::**OnFuncPtr)(char*);

	int TestFunc1(char* sParam)	{	return printf("TestFunc1:%s\n", sParam);	}
	int TestFunc2(char* sParam)	{	return printf("TestFunc2:%s\n", sParam);	}
	int TestFunc3(char* sParam)	{	return printf("TestFunc3:%s\n", sParam);	}


public:
	CTest1()
	{
		// int	 (CTest1::*OnFuncPtr	[4])(char*);위의 이부분을 동적으로 할당한다면
		OnFuncPtr = new (int (CTest1::*[4])(char*));

		OnFuncPtr[0] = TestFunc1;
		OnFuncPtr[1] = TestFunc2;
		OnFuncPtr[2] = TestFunc3;
	}

	virtual ~CTest1()
	{
		if(OnFuncPtr)
		{
			delete [] OnFuncPtr;
			OnFuncPtr = NULL;
		}
	}

	
	void	OnFuncPtrCall(int nIdx, char* sParam)
	{
		(this->*OnFuncPtr[nIdx])(sParam);
	}
};



int main()
{
	printf("함수 포인터 연습\n\n");


	printf("1. 보편적인 함수 호출 코딩.-----\n\n");

	int (*FuncPtr)(char* sParam);
	FuncPtr = TestFunc1;
	FuncPtr("Test string: 123456ABC");


	printf("\n\n2. 변수에 함수 포인터 저장.(잘 사용안함)-----\n\n");
	
	int nFunc1 = 0;
	int nFunc2 = 0;
	nFunc1 = (int)TestFunc1;												// 함수의 주소를 가져온다.
	((int (__cdecl *)(char *))nFunc1)("Test string1: 123456ABC");

	nFunc2 = (int)TestFunc2;
	((int (*)(char *))nFunc2)("Test string2: 123456ABC");




	printf("\n\n3. 배열 함수 포인터 사용하기-----\n\n");
	int (*FuncPtrArr[3])(char* sParam);

	FuncPtrArr[0] = TestFunc1;
	FuncPtrArr[1] = TestFunc2;
	FuncPtrArr[2] = TestFunc3;
	
	FuncPtrArr[0]("Test string1");
	FuncPtrArr[1]("Test string2");
	FuncPtrArr[2]("Test string3");


	printf("\n\n4. 클래스에서 함수 포인터 사용하기-----\n\n");
	
	CTest1	pCls;
	pCls.OnFuncPtrCall(0, "Test str1");
	pCls.OnFuncPtrCall(1, "Test str2");
	pCls.OnFuncPtrCall(2, "Test str3");
	
	return 1;
}