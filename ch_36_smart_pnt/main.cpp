#include <stdio.h>

class RefCount
{
private:
	int crefs;
	
public:
	RefCount()
	{
		crefs = 0;
	}
	
	~RefCount()
	{
		printf("goodbye(%d)\n", crefs);
	}
	
	void upcount()
	{
		++crefs;
		printf("up to %d\n", crefs);
	}
	
	void downcount()
	{
		if(--crefs == 0)
			delete this;
		else
			printf("downto %d\n", crefs);
	}
};


class Sample : public RefCount
{
public:
	void doSomething()
	{
		printf("Did something\n");
	}
};



template <class T>
class Ptr
{
	T* p;
public:
	Ptr(T* p_);
	~Ptr();
	
	operator T*();	
	T& operator*();	
	T* operator->();
	Ptr& operator=(Ptr<T> &p_);	
	Ptr& operator=(T* p_);
};


template <class T>
Ptr<T>::Ptr(T* p_) : p(p_)	{	p->upcount();		}

template <class T>
Ptr<T>::~Ptr()				{	p->downcount();		}

template <class T>
Ptr<T>::operator T*()
{
	return p;
}

template <class T>
T& Ptr<T>::operator*()
{
	return *p;
}

template <class T>
T* Ptr<T>::operator->()
{
	return p;
}

template <class T>
Ptr<T>& Ptr<T>::operator=(Ptr<T> &p_)
{
	return operator=((T *) p_);
}

template <class T>
Ptr<T>& Ptr<T>::operator=(T* p_)
{
	p->downcount();
	p = p_;
	p->upcount();

	return *this;
}


int main()
{
	printf("스마트 포인터 예제:MSDN펌\n");
	
	Ptr<Sample> p  = new Sample; // sample #1
	Ptr<Sample> p2 = new Sample; // sample #2
	
	// #1 will have 0 crefs, so it is destroyed;
	p = p2;
	
	// #2 will have 2 crefs.
	p->doSomething();
	
	return 0;
	// As p2 and p go out of scope, their destructors call
	// downcount. The cref variable of #2 goes to 0, so #2 is
	// destroyed
}
