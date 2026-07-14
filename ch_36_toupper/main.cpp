

#include <stdio.h>

void main()
{
	char	s[] = "¾È³ç Hello ÇÏ¼¼¿ä world";
	char*	p = s;

	for(; *p != 0; ++p)
	{
		if( 'A' <=*p && *p <= 'Z')
			*p |= 0x20;	// 0010 0000;
	}


	printf("%s\n", s);
}