

#include <stdio.h>
#include "Tscanf.h"
#include "TscanfA.h"
#include "TscanfB.h"

int main( void )
{
	char s1[32] ={0};
	char s2[32] ={0};
	char s3[32] ={0};
	char s4[32] ={0};
	
	
	int a1	= 0;
	int a2	= 0;
	int a3	= 0;
	int a4	= 0;
	
	char s[] ="123 456 789 101";
	
	//	sscanf(s, "%*s %d %*s %d", &a1, &a2);
	
	Tscanf(s, "%*s %d %*s %d", &a1, &a2);
	 
	return 1;
}





