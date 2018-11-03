
#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int FindMaxPattern(int* dstPos, int* dstLen, const char* sSrc, int lenSrc)
{
	//char	sSrc[]="abcbabdbe";

	int		retMax = 0;			// 출력용 최대 패턴 길이
	int		retCnt = 0;			// 출력용 최대 패턴 숫자
	int		retLen = 0;			// 출력용 최종 패턴 키 길이
	char*	retDst = NULL;		// 출력용 최종 패턴 시작 위치

	int		ptnCnt = 0;			// 임시 패턴 숫자
	int		ptnMax = 0;			// 임시 패턴 최대 길이
	char*	ptnKey = NULL;		// 패턴 키
	char*	ptnBgn = NULL;		// 패턴 시작 위치


	int		n=0, k=0, i=0;
	int		end = 0;
	int		lenKey = 0;			// 패턴 키 길이


	char	sAsc[128]= {0};		// 문자 하나 체크용.


	*dstPos = -1;
	*dstLen = 0;


	if(NULL == sSrc || 1>=lenSrc)
		goto END;



	// 입력 문자열 길이의 절반만 수행
	for(n=0; n<lenSrc/2; ++n)
	{
		++lenKey;

		end = lenSrc - lenKey;	// 목적지 계산

		for(k=0; k<end; ++k)
		{

			// Key 생성

			ptnBgn = (char*)(sSrc+k);

			//[A-Za-z0-9] 가 아니면 건너뛴다.			
			if( ('A' > *ptnBgn || *ptnBgn > 'Z') &&
				('a' > *ptnBgn || *ptnBgn > 'z') &&
				('0' > *ptnBgn || *ptnBgn > '9') &&
				('A' > *ptnBgn || *ptnBgn > 'z')
				)
				continue;

			if(1 == lenKey)
			{
				if( 0 != sAsc[*ptnBgn])
					continue;

				sAsc[*ptnBgn] = 1;
			}


			// Key 위치 지정
			ptnKey = ptnBgn;


			// 패턴 숫자 초기화
			ptnCnt = 0;
			ptnMax = 0;


			// Key 가 만들어진 위치+ 키 길이 바로 다음부터 찾기 시작
			for(i= k+lenKey; i< end+1; )
			{
				if(0 == strncmp(sSrc+i, ptnKey, lenKey) )
				{
					++ptnCnt;
					 i += lenKey;	// 키를 찾았다면 길이만큼 증가
				}
				else
					 ++i;			// 못찾으면 1증가
			}

			if(0<ptnCnt)
			{
				++ptnCnt;	// 패턴은 2번 이상 나와야 하므로...
				ptnMax = ptnCnt * lenKey;
			}


			//M이 같다면 반복횟수가 더 많은 반복문자열을 출력한다.
			//M이 같고 반복횟수가 동일하다면 앞에 나온 문자열을 출력한다.

			// 이전 보다 큰 패턴을 찾는다.
			if(    retMax < ptnMax
			//	|| (retMax == ptnMax && ptnLen < lenKey)
				)
			{
				retMax = ptnMax;
				retCnt = ptnCnt;

				retLen = lenKey;
				retDst = ptnKey;
			}

			// 현재 처리하는 문자열에서 패턴이 없으면 다음에도 없음.
			if(1 == ptnCnt)
				goto END;
		}
	}


	if(0<retMax)
	{
		*dstPos = retDst - sSrc;
		*dstLen = retLen;
	}

END:
	return retCnt;
}


int PatternTest()
{
	char*	sExam[] =
	{
		"abcde ",
		"12aaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"ab12ab12abab1212 ",
		NULL,
	};



	for(int n=0; NULL != sExam[n]; ++n)
	{
		char*	src    = sExam[n];
		int		srcLen = strlen(src);
		int		dstPos = -1, dstLen = -1;

		int	r = FindMaxPattern(&dstPos, &dstLen, src, srcLen );

		if(0<r)
		{
			printf("Pattern: ");
			fwrite(src+ dstPos, sizeof(char), dstLen, stdout);
			printf(":%d\n", r);
		}

		else
			printf("Pattern: NULL\n");
	}


	return 0;
}



int PatternConsole()
{
	int		lenBuf = 1024 * 1024;
	int		lenRead = 1;

	char*	sSrc = NULL;


	sSrc = (char*)malloc(lenBuf +4);
	memset(sSrc, 0, lenBuf +4);


	while(1)
	{
		printf("패턴 찾기: 종료하려면 \'q\'를 입력하세요.\n");

		memset(sSrc, 0, lenRead);
		fgets(sSrc, lenBuf, stdin);

		lenRead = strlen(sSrc);

		if(2 >= lenRead)
		{
			if('q' == *sSrc)		// 프로그램 종료
				break;

			else					// 길이가 짧음
			{
				printf("길이가 짧아요.\n");
				continue;
			}
		}

		sSrc[lenRead] = 0;			// 개행 문자 처리
		--lenRead;


		int	dstPos = -1, dstLen = -1;
		int	r = FindMaxPattern(&dstPos, &dstLen, sSrc, lenRead );

		if(0<r)
		{
			printf("Pattern: ");
			fwrite(sSrc+ dstPos, sizeof(char), dstLen, stdout);
			printf(":%d\n", r);
		}

		else
			printf("Pattern: NULL\n\n");
	}


	printf("프로그램 종료\n");

	free(sSrc);

	return 0;
}



int PatternFile(int argc, char** argv)
{
	char*	sFileSrc = "F:/in.txt";
	char*	sFileDst = "F:/out.txt";

	char*	sSrc = NULL;
	FILE*	fi = NULL;			// source file
	FILE*	fo = NULL;			// dest file

	int		lenBuf = 0;
	int		lenRead = 1;


	if(3 > argc)
	{
		printf(	"Error:인수가 적습니다. "
				"입력 파일은 %s 출력 파일은 %s로 대처 합니다.\n"
				, sFileSrc, sFileDst
				);

		fi = fopen(sFileSrc, "rt");
		fo = fopen(sFileDst, "wt");
	}
	else
	{
		char*	sFileSrc = argv[1];
		char*	sFileDst = argv[2];

		fi = fopen(argv[1], "rt");	// source file
		fo = fopen(argv[2], "wt");	// dest file
	}


	if(NULL == fi)
	{
		printf("입력 파일을 열 수 없습니다.\n");
		return 0;
	}


	if(NULL == fo)
	{
		printf("출력 파일을 열 수 없습니다.\n");
		return 0;
	}

	fseek(fi, 0, SEEK_END);
	lenBuf = ftell(fi);
	fseek(fi, 0, SEEK_SET);


	sSrc = (char*)malloc( 4* ( (lenBuf +7)/4 ) );
	memset(sSrc, 0, 4* ( (lenBuf +7)/4 ) );


	lenRead = fread(sSrc, sizeof(char), lenBuf, fi);


	int	dstPos = -1, dstLen = -1;
	int	r = FindMaxPattern(&dstPos, &dstLen, sSrc, lenRead );


	if(0<r)
	{
		fwrite(sSrc+ dstPos, sizeof(char), dstLen, fo);
		fprintf(fo, ":%d\n", r);

		fwrite(sSrc+ dstPos, sizeof(char), dstLen, stdout);
		printf(":%d\n", r);
	}
	else
	{
		fprintf(fo, "NULL\n");
		printf("Pattern: NULL\n\n");
	}


	free(sSrc);

	fclose(fi);
	fclose(fo);

	return 0;
}




int main(int argc, char** argv)
{
	PatternTest();
	//PatternConsole();
	//PatternFile(argc, argv);

	return 0;
}

