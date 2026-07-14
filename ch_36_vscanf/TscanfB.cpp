
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>


#include "TscanfB.h"



int TscanfB(char* sBuf, char* format, ...)								// if Failed then returned -1. succeeded then returned Argument count.
{
	va_list ap;
	va_start(ap, format);

	
	int		i=0;
	
	int		nCnt=0;
	int		nArg=0;
	
	void*	pArg[64]={0};
	char	sFmt[64][512]={0};

	char	cCur;
	char*	sCur;
	char*	sBgn;
	

	nArg	= 0;
	sCur	= strchr(format, '%');
	sBgn	= sCur;

	if(NULL == sCur)
		return -1;

	do
	{
		++sCur;
		cCur = *sCur;

		if(NULL == cCur)
		{
		}
		else if( '*' == cCur)		// "%*"
		{
			++nCnt;
		}
		else if ( '%' == cCur)		// "%%"
		{
			++sCur;
		}
		else
		{
			pArg[nArg] = va_arg( ap, void* );

			for(i=0; i<nCnt; ++i)
			{
				strcat(sFmt[nArg], "%*s ");
			}

			char	sFmtSmall[16]={0};
			char*	sNxt = strchr( sCur, '%');

			if(sNxt)
			{
				int nSize = sNxt - sBgn;
				strncpy(sFmtSmall, sBgn, nSize);
				strcat(sFmtSmall, " ");
			}
			else
			{
				strcpy(sFmtSmall, sBgn);
			}


			strcat((char*)&sFmt[nArg], sFmtSmall);
			++nArg;
			++nCnt;

			if ( nArg >= 64 )
				return -1;
		}

		sCur	= strchr( sCur, '%');
		sBgn	= sCur;

	} while (NULL != sCur);

	va_end( ap );


	if(0==nArg)
		return -1;


	for(i=0; i<nArg; ++i)
		sscanf( sBuf, sFmt[i], pArg[i]  );

	return nArg;
}



