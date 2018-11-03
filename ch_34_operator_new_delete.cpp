#include <stdio.h>
#include <string.h>
#include <new>

class MyClass 
{
public:
	int m_iVal;

public: 
	MyClass()
	{
		printf("Construction MyClass.\n");
	}


	~MyClass()
	{
		printf("Destructing MyClass.\n");
	}

	void* operator new(size_t iSize)
	{
		printf("Call operator new(size_t, unsigned int)\n");
		void *p = malloc( iSize );
		return p;
	}

	void* operator new(size_t iSize, void* t) throw()
	{
		printf("Call operator new(size_t, unsigned int)\n");
		void *p = malloc( iSize );

		printf("The address of t: %x\n", t);
		memcpy(p, t, iSize );

		return p;
	}

	void* operator new(size_t iSize, const std::nothrow_t&) throw()
	{
		printf("Call operator new(size_t, const nothrow_t&)\n");
		void *p = malloc( iSize );
		return p;
	}

	void operator delete(void* pObj)
	{
		printf("Call operator delete(void*)\n");
		free(pObj);
	}

	void operator delete(void* pObj, void* memory) throw()
	{
		printf("Call operator delete(void*)\n");
		free(pObj);
	}

	void operator delete(void* pObj, const std::nothrow_t&) throw()
	{
		printf("Call operator delete(void*)\n");
		free(pObj);
	}



	void* operator new[](size_t iSize) throw()
	{
		printf("Call operator new[](size_t): size=>%d\n", iSize);
		void *p = malloc( iSize );

		return p;
	}

	void *operator new[](size_t iSize, void* t) throw()
	{
		printf("Call operator new[](size_t, unsigned int)\n");
		void *p = malloc( iSize );

		printf("The address of t: %x\n", t);
		memcpy(p, t, iSize );

		return p;
	}

	void *operator new[](size_t iSize, const std::nothrow_t&) throw()
	{
		printf("Call operator new[](size_t, const nothrow_t&)\n");
		void *p = malloc( iSize );
		return p;
	}



	void operator delete[](void* pObj)
	{
		printf("Call operator delete(void*)\n");
		free(pObj);
	}

	void operator delete[](void* pObj, void* memory) throw()
	{
		printf("Call operator delete(void*)\n");
		free(pObj);
	}

	void operator delete[](void* pObj, const std::nothrow_t&) throw()
	{
		printf("Call operator delete(void*)\n");
		free(pObj);
	}
};


void main() 
{
	{
		printf("The first form of new delete----------------\n");
		MyClass* ptr = new MyClass;
		delete ptr;
	}

	{
		printf("The second form of new delete---------------\n");
		char x[sizeof( MyClass )];
		MyClass* ptr = new( &x[0] ) MyClass;

		ptr -> ~MyClass();
		delete ptr;
	}

	{
		printf("The third form of new delete---------------\n");
		MyClass* ptr = new( std::nothrow ) MyClass;
		delete ptr;
	}



	{
		printf("The forth form of new delete----------------\n");

		int iSize = sizeof(MyClass);
		MyClass* ptr = new MyClass[10];
		delete [] ptr;
	}

}
