
#include <memory>

using namespace std;

#include <stdio.h>


struct MySt
{
	int* p;

	MySt()
	{
		p = new int[10000];
	}

	~MySt()
	{
		delete [] p;
	}
};

void Tst()
{
	MySt* p = new MySt;
	std::auto_ptr<MySt> c(p);

//	*c =100;
//	printf("%d\n", *c);
	int t;

	t=100;
}

int main(int argc, char** argv)
{
	Tst();
	
	return 0;
}