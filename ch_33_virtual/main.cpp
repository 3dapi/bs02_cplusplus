#include <stdio.h>


#define  USE_VIRTUAL	1

#if USE_VIRTUAL

struct ClassA
{
	virtual void PrintA()	{		printf("ClassA PrintA\n");	}
	virtual void PrintB()	{		printf("ClassA PrintB\n");	}
	virtual void PrintC()	{		printf("ClassA PrintC\n");	}
};


struct ClassB : public ClassA
{
	virtual void PrintA()	{		printf("ClassB PrintA\n");	}
	virtual void PrintB()	{		printf("ClassB PrintB\n");	}
};

#else

struct ClassA
{
	void PrintA()	{		printf("ClassA PrintA\n");	}
	void PrintB()	{		printf("ClassA PrintB\n");	}
	void PrintC()	{		printf("ClassA PrintC\n");	}
};


struct ClassB : public ClassA
{
	void PrintA()	{		printf("ClassB PrintA\n");	}
	void PrintB()	{		printf("ClassB PrintB\n");	}
};


#endif


void Print(ClassA* pTstA)
{
	pTstA->PrintA();
	pTstA->PrintB();
	pTstA->PrintC();
}


int main()
{
//	ClassA a;
//
//	a.PrintA();
//	a.PrintB();
//	a.PrintC();

	ClassB b;

	b.PrintA();
	b.PrintB();
	b.PrintC();

	printf("\n----------------\n");
	
	Print(&b);


	return 1;
}