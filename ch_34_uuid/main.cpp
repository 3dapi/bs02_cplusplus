
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "Rpcrt4.lib")

#include <objbase.h>
#include <Rpcdce.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LnUtil_UuidGen(void* pGuid/*Must be Minimum 16Bytes*/, char* sGuid /*Must be Minimum 64Bytes*/)
{
	BYTE*		sTud;
	HRESULT		hr1 = UuidCreate((GUID*)pGuid);
	RPC_STATUS	hr2 = UuidToString((GUID*)pGuid, &sTud);
	GUID*	pGd = (GUID*)pGuid;
	
	strcpy( sGuid, (char*)sTud);
	RpcStringFree(&sTud);	
}


void main()
{
	GUID	dGuid;
	char	sGuid[64]={0};
	
	LnUtil_UuidGen(&dGuid, sGuid);
	
	printf("%s\n",sGuid);
}