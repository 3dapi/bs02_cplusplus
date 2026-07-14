
#include <Windows.h>
#include <stdio.h>


// This is a Bigendian.
struct _TLcId
{
	union
	{
		struct
		{
			union
			{
				struct
				{		
					union	{	WORD _d;	WORD _I4;	};
					union	{	WORD _c;	WORD _I3;	};
				};

				DWORD	S;
			};

			union
			{
				struct
				{
					union	{	WORD _b;	WORD _I2;	};
					union	{	WORD _a;	WORD _I1;	};
				};

				DWORD	M;
			};
		};

		ULONGLONG _Id;
	};

	_TLcId(): _Id(0xFFFFFFFFFFFFFFFF)	{}
	_TLcId(WORD I1,WORD I2=0xFFFF,WORD I3=0xFFFF,WORD I4=0xFFFF): _I1(I1),_I2(I2),_I3(I3),_I4(I4)	{}
	_TLcId(ULONGLONG I) : _Id(I){}

	void		SetId(WORD I1=0xFFFF,WORD I2=0xFFFF,WORD I3=0xFFFF,WORD I4=0xFFFF){_I1=I1;_I2=I2;_I3=I3;_I4=I4;}
	void		SetId(ULONGLONG Id=0xFFFFFFFFFFFFFFFF){	_Id = Id;	}
	void		SetId1(WORD I1=0xFFFF)	{	_I1 = I1;	}
	void		SetId2(WORD I2=0xFFFF)	{	_I2 = I2;	}
	void		SetId3(WORD I3=0xFFFF)	{	_I3 = I3;	}
	void		SetId4(WORD I4=0xFFFF)	{	_I4 = I4;	}

	ULONGLONG	GetId()		{	return _Id;	}
	WORD		GetId1()	{	return _I1;	}
	WORD		GetId2()	{	return _I2;	}
	WORD		GetId3()	{	return _I3;	}
	WORD		GetId4()	{	return _I4;	}

	DWORD		GetM()		{	return M;	}
	DWORD		GetS()		{	return S;	}
};

int main( void )
{

	_TLcId tt;

	tt.SetId1(0x1234);
	tt.SetId2(0x5678);
	tt.SetId3(0xdead);
	tt.SetId4(0xbeef);


	printf("%x\n", tt.GetM());
	printf("%x\n", tt.GetS());
	printf("%I64x\n", tt.GetId());


	return 0;
}





