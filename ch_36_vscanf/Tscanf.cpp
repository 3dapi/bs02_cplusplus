
#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>

#include "Tscanf.h"

//	I don't how many time I've been irritated by the fact that Microsoft
//	chose to implement all the v*printf family of routines, but for some
//	odd reason decided to leave out all the v*scanf routines.It is all the more frustrating that the functionality is actually
//	present inside their crt library (in a function called input, which is
//	not exported).>From there your choices are as follows:	- Write your own vsscanf
//		- Rip the source out of crt and graft it into your app.
//		- Use a third party implementation (trio is a good one, btw).All these solutions suck: if you choose to write your own, you'll soon
//	discover how hard it is to write an ANSI conforming scanf, other than
//	hacking together Frankenstein code that is half yours, and half calling
//	the native system sscanf when things gets hard (float conversion springs
//	to mind).If you choose a third party implementation (crt, trio, glibc, ...), there's
//	the usual problems: it's usually much bulkier than you'd like, doesn't compile
//	the way you have your tree setup, comes with hieroglyphic Makefiles, carries crual
//	and unusual licensing agreements, and basically adds a maintenance burden to your
//	already complicated work day.
//		
//	Given all this, and the fact that irritation always ends up breeding code,
//	here's my solution to the problem: since sscanf is available in the system,
//	I've implemented vsscanf by hacking together a fake stack before hoping into sscanf.Advantages:
//		- It works
//		- It is small
//		- It has no strings attached
//		- In time, it inherits all maintenance work done by MSFT on scanfDisadvantages:
//		- It adds a tiny overhead (browsing the fmt for % signs)
//		- It is not portable (although the technique is)
//		- But then again the rest of the universe *does* implement
//		  vsscanf, so who cares.Enjoy,	- mgixPS: This is written with Visual C++ inline assembly. If someone gets
//	around to writing the equivalent in the weird gcc inline assembly linguo,
//	please send it my way. Thanks.*//*
//
//	 * vsscanf for Win32
//	 *
//	 * Written 5/2003 by <mgix@mgix.com>
//	 *
//	 * This code is in the Public Domain
//	 *
//	http://www.flipcode.com/cgi-bin/fcarticles.cgi?show=4&id=64176
 



int vsscanf(const char* sBuf, const char* format, va_list ap)
{
	// Get an upper bound for the # of args
	size_t count = 0;
	const char *p = format;

	while(1)
	{
		char c = *(p++);
		if(c==0) break;
		if(c=='%' && (p[0]!='*' && p[0]!='%')) ++count;
	}    // Make a local stack
	
	size_t stackSize = (2+count)*sizeof(void*);
	void **newStack = (void**)alloca(stackSize);    // Fill local stack the way sscanf likes it
	
	newStack[0] = (void*)sBuf;
	newStack[1] = (void*)format;
	memcpy(newStack+2, ap, count*sizeof(void*));    // Warp into system sscanf with new stack
	
	int result;
	void *savedESP;
	
	_asm
	{
		mov     savedESP, esp;
		mov     esp, newStack;
		call    sscanf;
		mov     esp, savedESP;
		mov     result, eax;
	}
	
	return result;
} 



int Tscanf(char* sBuf, char* format, ...)								// if Failed then returned -1. succeeded then returned Argument count.
{
	va_list ap;
	va_start(ap, format);
	
	return vsscanf(sBuf, format, ap);
}

