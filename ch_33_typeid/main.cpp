
#include <iostream>
#include <typeinfo.h>

class CclassA
{
public:
	virtual void Func()
	{
	}
};

class CclassB : public CclassA
{
};


class CclassC : public CclassB
{
};

class CclassD : public CclassC
{
};

int main()
{
	CclassD* pD = new CclassD ;
	CclassC* pC = pD;
	CclassB* pB = pC;
	CclassA* pA = pB;
	
	
	std::cout << typeid( pA ).name() << std::endl;
	std::cout << typeid(*pA ).name() << std::endl;
	std::cout << typeid( pB ).name() << std::endl;
	std::cout << typeid(*pB ).name() << std::endl;
	std::cout << typeid( pC ).name() << std::endl;
	std::cout << typeid(*pC ).name() << std::endl;
	std::cout << typeid( pD ).name() << std::endl;
	std::cout << typeid(*pD ).name() << std::endl;
	delete pD;
	
	return 1;
}