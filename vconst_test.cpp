
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Windows.h>


struct MySt
{
	char* sMsg;
	
	const char* const GetText() const
	{
		return sMsg;
	}
};


/*
#include <stdio.h>

#include <stdlib.h>
#include <stdio.h>

void main()
{
	char *temp;
	temp = getenv( "PATH" );
	printf( "Path: %s\nenviron: %x\n", temp, environ );
}
*/


void main()
{
	MySt st;

	st.sMsg = new char[128];

	memset(st.sMsg, 0, 128);

	const char* const p = st.GetText();

	//p = NULL;

	strcpy((char*)p, "Hello world");

	printf("%s\n", st.GetText());

}