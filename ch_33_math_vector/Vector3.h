// Interface for the CVector3 class.
//
//////////////////////////////////////////////////////////////////////


#ifndef _VECTOR3_H_
#define _VECTOR3_H_

class CVector3
{
public:
	union
	{
		struct 
		{
			float x;
			float y;
			float z;
		};

		float m[3];
	};
	

public:
	CVector3();
	CVector3( float X, float Y, float Z);
	CVector3( float *p );
	CVector3( CVector3& rhs );
	
	// casting
	operator float* ();

	CVector3& operator += ( CVector3& rhs );
	CVector3& operator -= ( CVector3& rhs );
	CVector3& operator *= ( float f );
	CVector3& operator /= ( float f );
	
	CVector3 operator + ( CVector3& rhs );
	friend CVector3 operator - ( CVector3& a, CVector3& b );					// 이부분 주의... 인자를 두개 받을 경우에는 friend이외에 달리 방법이 없다.

	CVector3 operator * ( float f );
	CVector3 operator / ( float f );
	
	friend CVector3 operator * ( float f, CVector3& rhs );	
	bool operator == ( CVector3& rhs );
	bool operator != ( CVector3& rhs );
};


#endif