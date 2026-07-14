
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "TscanfA.h"

#define ADD_ARGS_1  pArg[0]
#define ADD_ARGS_2  pArg[0], pArg[1]
#define ADD_ARGS_3  pArg[0], pArg[1], pArg[2]
#define ADD_ARGS_4  pArg[0], pArg[1], pArg[2], pArg[3]
#define ADD_ARGS_5  pArg[0], pArg[1], pArg[2], pArg[3], pArg[4]
#define ADD_ARGS_6  pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5]
#define ADD_ARGS_7  pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6]
#define ADD_ARGS_8  pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6], pArg[7]
#define ADD_ARGS_9  pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6], pArg[7], pArg[8]
#define ADD_ARGS_10 pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6], pArg[7], pArg[8], pArg[9]
#define ADD_ARGS_11 pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6], pArg[7], pArg[8], pArg[9], pArg[10]
#define ADD_ARGS_12 pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6], pArg[7], pArg[8], pArg[9], pArg[10], pArg[11]
#define ADD_ARGS_13 pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6], pArg[7], pArg[8], pArg[9], pArg[10], pArg[11], pArg[12]
#define ADD_ARGS_14 pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6], pArg[7], pArg[8], pArg[9], pArg[10], pArg[11], pArg[12], pArg[13]
#define ADD_ARGS_15 pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6], pArg[7], pArg[8], pArg[9], pArg[10], pArg[11], pArg[12], pArg[13], pArg[14]
#define ADD_ARGS_16 pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6], pArg[7], pArg[8], pArg[9], pArg[10], pArg[11], pArg[12], pArg[13], pArg[14], pArg[15]
#define ADD_ARGS_17 pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6], pArg[7], pArg[8], pArg[9], pArg[10], pArg[11], pArg[12], pArg[13], pArg[14], pArg[15], pArg[16]
#define ADD_ARGS_18 pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6], pArg[7], pArg[8], pArg[9], pArg[10], pArg[11], pArg[12], pArg[13], pArg[14], pArg[15], pArg[16], pArg[17]
#define ADD_ARGS_19 pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6], pArg[7], pArg[8], pArg[9], pArg[10], pArg[11], pArg[12], pArg[13], pArg[14], pArg[15], pArg[16], pArg[17], pArg[18]
#define ADD_ARGS_20 pArg[0], pArg[1], pArg[2], pArg[3], pArg[4], pArg[5], pArg[6], pArg[7], pArg[8], pArg[9], pArg[10], pArg[11], pArg[12], pArg[13], pArg[14], pArg[15], pArg[16], pArg[17], pArg[18], pArg[19]



int TscanfA(char *input, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
		
	int			nArgs=0;
	
	void*		pArg[64]={0};
	char		sFmt[64][16]={0};
	char*		sCur;
	char*		sTmp;
	char		cCur;

	nArgs	= 0;
	sCur	= strchr(format, '%');
	sTmp	= sCur;

	if(NULL == sCur)
		return 0;

	do
	{
		++sCur;
		cCur = *sCur;

		if(NULL == cCur)
		{
		}
		else if( '*' == cCur)		// "%*"
		{
		}
		else if ( '%' == cCur)		// "%%"
		{
			++sCur;
		}
		else
		{
			if ( nArgs >= 64 )
				return 0;

			pArg[nArgs] = va_arg( ap, void* );


			char*		sNxt = strchr( sCur, '%');
			strcpy(sFmt[nArgs], format);


			++nArgs;
		}

		sCur	= strchr( sCur, '%');
		sTmp	= sCur;

	} while (NULL != sCur);

	va_end( ap );


	if(0==nArgs)
		return 0;


	
	
	switch ( nArgs )
	{
	case  1: return sscanf( input, format, ADD_ARGS_1  );
	case  2: return sscanf( input, format, ADD_ARGS_2  );
	case  3: return sscanf( input, format, ADD_ARGS_3  );
	case  4: return sscanf( input, format, ADD_ARGS_4  );
	case  5: return sscanf( input, format, ADD_ARGS_5  );
	case  6: return sscanf( input, format, ADD_ARGS_6  );
	case  7: return sscanf( input, format, ADD_ARGS_7  );
	case  8: return sscanf( input, format, ADD_ARGS_8  );
	case  9: return sscanf( input, format, ADD_ARGS_9  );
	case 10: return sscanf( input, format, ADD_ARGS_10 );
	case 11: return sscanf( input, format, ADD_ARGS_11 );
	case 12: return sscanf( input, format, ADD_ARGS_12 );
	case 13: return sscanf( input, format, ADD_ARGS_13 );
	case 14: return sscanf( input, format, ADD_ARGS_14 );
	case 15: return sscanf( input, format, ADD_ARGS_15 );
	case 16: return sscanf( input, format, ADD_ARGS_16 );
	case 17: return sscanf( input, format, ADD_ARGS_17 );
	case 18: return sscanf( input, format, ADD_ARGS_18 );
	case 19: return sscanf( input, format, ADD_ARGS_19 );
	case 20: return sscanf( input, format, ADD_ARGS_20 );
	}

	return nArgs;
}



