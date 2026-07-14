////////////////////////////////////////////////////////////////////////////////
// 
// Explain: Struct와 class는 같다.
// 단지 struct의 기본 접근권한은 public이고 
// class는 private 이다.
// 아래의 예제에서 class대신 struct를 사용해도 된다.
// class(혹은 struct)와 union을 잘 결합시키면 데이터 구조에 도움이 된다.


#include <stdio.h>


class Vector3
{
public:
	union
	{
		class
		{
		public:	
			float x;
			float y;
			float z;
		};

		float m[3];
	};

	Vector3();
	Vector3(float X, float Y, float Z);
	Vector3(Vector3 & rhs);
	
	~Vector3();

	void VectorAdd(Vector3& vcOut, Vector3& vc1, Vector3& vc2); 
	
};


Vector3::Vector3()
:	x	(0.f)
,	y	(0.f)
,	z	(0.f)
{
}

Vector3::Vector3(float X, float Y, float Z)
:	x	(X)
,	y	(Y)
,	z	(Z)
{
}

Vector3::Vector3(Vector3 & rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}


Vector3::~Vector3()
{
}



Vector3 pos1;
Vector3 pos2;





int main()
{
	pos1.x = 1;	pos1.y = 2;	pos1.z = 3;
	pos2.x = 4;	pos2.y = 5;	pos2.z = 6;

	Vector3 c(pos2);

	printf("%f    %f    %f\n", c.x, c.y, c.z);

	c .VectorAdd(c, pos1, pos2);

	printf("%f    %f    %f\n", c.x, c.y, c.z);
	return 0;
}




void Vector3::VectorAdd(Vector3& vcOut, Vector3& vc1, Vector3& vc2)
{
	vcOut.x = vc1.x + vc2.x;
	vcOut.y = vc1.y + vc2.y;
	vcOut.z = vc1.z + vc2.z;
}