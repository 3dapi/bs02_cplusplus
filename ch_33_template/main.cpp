// main.cpp
//
//////////////////////////////////////////////////////////////////////

#include "_StdAfx.h"


INT	SumInt(INT* pAr, INT N)
{	
	INT	i;
	INT	iS = 0;

	for(i=0; i<N; ++i)
	{
		iS += pAr[i];
	}

	return iS;
}

FLOAT SumFloat(FLOAT* pAr, INT N)
{	
	INT	i;
	FLOAT	iS = 0;

	for(i=0; i<N; ++i)
	{
		iS += pAr[i];
	}

	return iS;
}


template<class T>
T SumTemplate(T* pA, INT N)
{	
	INT	i;
	T	iS = 0;

	for(i=0; i<N; ++i)
	{
		iS += pA[i];
	}

	return iS;
}





void BindDeleteOperator()
{
	ClassA* pA;
	ClassB* pB;
	ClassC* pC;

	NewInit(pA);
	NewInit(pB);
	NewInit(pC);

	Delete(pA);
	Delete(pB);
	Delete(pC);
}


void main()
{
	INT i;

	INT* pArInt = NULL;
	INT iTotal;

	pArInt = new INT[10];

	for(i=0; i<10; ++i)
		pArInt[i] = i;

	printf("\n-----------------------Template Test for Function-----------------------\n\n");

	printf("Function SumInt() -----------------------\n");
	iTotal = SumInt(pArInt, 5);
	
	printf("%f\n\n", DOUBLE(iTotal));



	
	FLOAT* pArFloat = NULL;
	FLOAT fTotal;

	pArFloat = new FLOAT[10];
	for(i=0; i<10; ++i)
		pArFloat[i] = FLOAT(i*i);

	printf("Function SumFloat() -----------------------\n");
	fTotal = SumFloat(pArFloat, 5);
	printf("%f\n\n", DOUBLE(fTotal));




	printf("Function SumTemplate() -----------------------\n");
	printf("INT: %f\n", DOUBLE(SumTemplate(pArInt, 5)));
	printf("FLOAT: %f\n\n", DOUBLE(SumTemplate(pArFloat, 5)));

	delete pArInt;
	delete pArFloat;



	printf("\n-----------------------Template Test for Class-----------------------\n\n");

	printf("AdderInt class -----------------------\n");
	CAdderInt	AdderInt;
	for(i=0; i<10; ++i)
		AdderInt.Add( i);

	printf("%f\n\n", DOUBLE(AdderInt.Sum()));


	printf("AdderFloat class -----------------------\n");
	CAdderFloat	AdderFloat;
	for(i=0; i<10; ++i)
		AdderFloat.Add( FLOAT(i*i));
	
	printf("%f\n\n", DOUBLE(AdderFloat.Sum()));


	printf("AdderTemplate class -----------------------\n");
	CAdderT<FLOAT>	AdderT;
	for(i=0; i<10; ++i)
		AdderT.Add( FLOAT(i*i));
	printf("%f\n\n", DOUBLE(AdderT.Sum()));


	printf("\n-----------------------Multi-Template Test for Class-----------------------\n\n");

	CTmpMulti<FLOAT,INT,DOUBLE, 10, 20.05>	fTst;

	for(i=0; i<5; ++i)
	{
		fTst.t1[i] = FLOAT(i*i);
		fTst.t2[i] = i;
		fTst.t3[i] = DOUBLE(i*i*i);
	}

	printf("%f\n", DOUBLE(fTst.GetT1(3) ) );
	printf("%f\n", DOUBLE(fTst.GetT2(3) ) );
	printf("%f\n", DOUBLE(fTst.GetT3(3) ) );



	printf("\n-----------------------Using Template Wrapping delete Operator-----------------------\n\n");
	BindDeleteOperator();
}
