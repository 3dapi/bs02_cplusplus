////////////////////////////////////////////////////////////////////////////////
// 
// Explain: 함수 오버로딩

#include <stdio.h>

// 1. Function OverRiding
// 잘 될까?

void	FunctionOverRiding();
void	FunctionOverRiding(int iA);
float	FunctionOverRiding(float fA);
float	FunctionOverRiding(int iA, float fA);
int		FunctionOverRiding(int iA, float fB, double dC);
float	FunctionOverRiding(int iA, float fB, float fC=0.f);


int main()
{
	printf("Function over riding Test-----------------------------\n");

//	FunctionOverRiding();
//	FunctionOverRiding(10);
//	FunctionOverRiding(20.f);
//	FunctionOverRiding(30, 40.f);
//	FunctionOverRiding(40, 50.f, 60.);
//	FunctionOverRiding(50, 60.f);

	return 1;
}


void FunctionOverRiding()
{
	printf("FunctionOverRiding()\n");
}

void FunctionOverRiding(int iA)
{
	printf("FunctionOverRiding(%d)\n", iA);
}

float	FunctionOverRiding(float fA)
{
	printf("FunctionOverRiding(%f)\n", fA);

	return fA;
}

float FunctionOverRiding(int iA, float fA)
{
	printf("FunctionOverRiding(%d, %f)\n", iA, fA);

	return fA;
}

int	FunctionOverRiding(int iA, float fB, double dC)
{
	printf("FunctionOverRiding(%d, %f %f %f)\n", iA, fB, dC);

	return iA;
}

float FunctionOverRiding(int iA, float fB, float fC)
{
	printf("FunctionOverRiding(%d, %f %f)\n", iA, fC);

	return (float)iA;
}
