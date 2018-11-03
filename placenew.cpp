#include <iostream>

using namespace std;


class MyClass
{
public:
	
	int num;


	MyClass()
	{
		num = 100;
		printf("%d\n", num);
	}
	
	MyClass(int i) : num(i)
	{
		printf("%d\n", num);
	}

	~MyClass()
	{
		printf("destroy\n");
	}
};


int main()
{

	void* t = malloc( sizeof(MyClass) );
	
	MyClass* p = NULL;

	p = new (t) MyClass();



	//delete buf;

	delete (p, p);

	














//
//
//
//	cout << "dumping MyClass* array\n";
//
//	for(i=0; i<10; ++i)
//	{
//		cout << p[i]->num << " ";
//	}
//	cout << endl;
//	
//	cout << "dumping buf as MyClass Array\n";
//
//	MyClass* C_array = reinterpret_cast<MyClass*>(buf);
//
//	for(i=0; i<10; ++i)
//	{
//		cout << C_array[i].num << " ";
//	}
//	cout << endl;
//	
	return 0;
}
