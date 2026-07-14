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
	
public:
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
	
	
	operator +=(Vector3& vcR)
	{
		this->x +=vcR.x;
		this->y +=vcR.y;
		this->z +=vcR.z;
	}
	
	
	Vector3 operator +(Vector3& vcR) const
	{
		return Vector3(this->x + vcR.x, this->y + vcR.y,this->z + vcR.z);
	}
	
	// friend in operator
	friend	Vector3 operator -(Vector3& vcR1, Vector3& vcR2)
	{
		return Vector3(vcR1.x - vcR2.x, vcR1.y - vcR2.y,vcR1.z - vcR2.z);
	}
	

	// Another friend applicaton
	friend void Print(Vector3& vcR);
	
};





void Print(Vector3& vcR)
{
	printf("%f    %f    %f\n", vcR.x, vcR.y, vcR.z);
}




int main()
{
	printf("--------------------Operator and Friend--------------------\n");

	Vector3 pos1(1, 2, 3);
	Vector3 pos2(4, 5, 6);
	
	Vector3 c(pos2);
	
	
	Print(c);
	
	c = pos1 + pos2;
	Print(c);
	
	c = pos1 - pos2;
	Print(c);
	
	return 0;
}





