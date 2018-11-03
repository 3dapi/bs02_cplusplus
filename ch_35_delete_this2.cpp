

#include <complex>

#include <stdio.h>
#include <math.h>


class MyClass
{
protected:
	int*	m_pMem;

public:
	MyClass()
	{
		m_pMem = (int*)malloc(10000000);
	}

	virtual ~MyClass()
	{
		Destroy();
	}

	void Destroy()
	{
		if(m_pMem)
		{
			free(m_pMem);
			m_pMem = NULL;
		}
	}

	int Release()
	{
		delete this;
		return 0;
	}


};

int main(int argc, char** argv)
{
	//_complex t;

	MyClass* mm = new MyClass;

	mm->Release();
	mm = NULL;

	return 0;
}