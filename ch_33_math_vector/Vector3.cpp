// Implementation for the CVector3 class.
//
//////////////////////////////////////////////////////////////////////


#include "Vector3.h"


CVector3::CVector3()
:	x	(0.f)
,	y	(0.f)
,	z	(0.f)
{
};

CVector3::CVector3( float *p )
{
	if(!p)
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}
	
	x = p[0];
	y = p[1];
	z = p[2];
}


CVector3::CVector3( CVector3& rhs )
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}

CVector3::CVector3( float X, float Y, float Z )
:	x	(X)
,	y	(Y)
,	z	(Z)
{
}

// casting
CVector3::operator float* ()
{
	return (float *) &x;
}


CVector3& CVector3::operator += ( CVector3& rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

CVector3& CVector3::operator -= ( CVector3& rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

CVector3& CVector3::operator *= ( float f )
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

CVector3& CVector3::operator /= ( float f )
{
	float fI = 1.0f / f;
	x *= fI;
	y *= fI;
	z *= fI;
	return *this;
}


CVector3 CVector3::operator + ( CVector3& rhs )										// Add
{
	return CVector3(x + rhs.x, y + rhs.y, z + rhs.z);
}


CVector3 operator - ( CVector3& a, CVector3& b )						// 이부분 주의... 인자를 두개 받을 경우에는 friend이외에 달리 방법이 없다.
{
	return CVector3(a.x - b.x, a.y - b.y, a.z - b.z);
}


CVector3 CVector3::operator * ( float f )
{
	return CVector3(x * f, y * f, z * f);
}

CVector3 CVector3::operator / ( float f )
{
	float fI = 1.f / f;
	return CVector3(x * fI, y * fI, z * fI);
}

CVector3 operator * ( float f, CVector3& rhs )
{
	return CVector3(f * rhs.x, f * rhs.y, f * rhs.z);
}

bool CVector3::operator == ( CVector3& rhs )
{
	return x == rhs.x && y == rhs.y && z == rhs.z;
}

bool CVector3::operator != ( CVector3& rhs )
{
	return x != rhs.x || y != rhs.y || z != rhs.z;
}

