#include <stdio.h>
#include <windows.h>


class Tdelete
{
public:
	DWORD a;
	DWORD b;
	DWORD c;

public:

	Tdelete()
	{
		memset( (void*)this, 0, sizeof(*this) );
	}

	Tdelete(DWORD c_)
	{
		c=c_;
	}


	Tdelete* DeleteThis()
	{
		printf("Before Delete: 0x%X c: 0X%X	&c: 0x%X\n", this, c, &c);
		delete this;
		printf("After  Delete: 0x%X c: 0X%X	&c: 0x%X\n", this, c, &c);

		return NULL;
	}


	void PrintC()
	{
		printf("this: 0x%X c: 0x%X	&c: 0x%X\n", this, c, &c);
	}

	virtual ~Tdelete()
	{
		printf("Delete this: 0x%X		\n", this);
	}
};



int main()
{
	Tdelete*	pTst1 = new Tdelete(0);
	Tdelete*	pTst2 = new Tdelete(1);
	Tdelete*	pTst3 = new Tdelete(2);
	Tdelete*	pTst4 = new Tdelete(3);
	Tdelete*	pTst5 = new Tdelete(4);


	pTst1->PrintC();
	pTst2->PrintC();
	pTst3->PrintC();
	pTst4->PrintC();
	pTst5->PrintC();

	printf("\n");

	pTst1 = pTst1->DeleteThis();
	pTst2->DeleteThis();
	pTst3->DeleteThis();
	pTst4->DeleteThis();
	pTst5->DeleteThis();

	printf("\n");

//	pTst1->PrintC();
//	pTst2->PrintC();
//	pTst3->PrintC();
//	pTst4->PrintC();
//	pTst5->PrintC();


	return 1;
}