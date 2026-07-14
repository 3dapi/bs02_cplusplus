#include < stdio.h>

class CTst
{
private:
	int iA;
	int iB;
	int iC;
	
	
public:
	CTst()
	{
		iA =10;
		iA =20;
		iA =30;
	}
	
	int GetA() { return iA; }
	int GetB() { return iB; }
	int GetC() { return iC; }
};

int main()
{
	CTst a;
	int *d;
	
	for(int i=0; i<3; ++i)
	{
		d = (int*) &*( (int*)&(a) + i);
		*d = i * i + i*10;
	}
	
	printf("%d\n", a.GetA());
	printf("%d\n", a.GetB());
	printf("%d\n", a.GetC());
	
	return 0;
}