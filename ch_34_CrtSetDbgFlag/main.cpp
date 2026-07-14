/*
* This program concentrates on allocating and freeing memory
* blocks to test the functionality of the _crtDbgFlag flag..
*/

#include <string.h>
#include <malloc.h>
#include <crtdbg.h>

void main( )
{
	char *p1, *p2;
	int tmpDbgFlag;
	
	/*
	* Set the debug-heap flag to keep freed blocks in the
	* heap's linked list - This will allow us to catch any
	* inadvertent use of freed memory
	*/
	tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpDbgFlag |= _CRTDBG_DELAY_FREE_MEM_DF;
	tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(tmpDbgFlag);
	
	/*
	* Allocate 2 memory blocks and store a string in each
	*/
	p1 = (char*)malloc( 134 );
	p2 = (char*)malloc( 138 );

	strcpy( p1, "p1 points to a Normal allocation block" );
	strcpy( p2, "p2 points to a Client allocation block" );
	
	/*
	* Free both memory blocks
	*/
	free( p2 );
	free( p1 );
	
	/*
	* Set the debug-heap flag to no longer keep freed blocks in the
	* heap's linked list and turn on Debug type allocations (CLIENT)
	*/
	tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpDbgFlag |= _CRTDBG_ALLOC_MEM_DF;
	tmpDbgFlag &= ~_CRTDBG_DELAY_FREE_MEM_DF;
	_CrtSetDbgFlag(tmpDbgFlag);
	
	/*
	* Explicitly call _malloc_dbg to obtain the filename and line number
	* of our allocation request and also so we can allocate CLIENT type
	* blocks specifically for tracking
	*/
	p1 = (char*)_malloc_dbg( 40, _NORMAL_BLOCK, __FILE__, __LINE__ );
	p2 = (char*)_malloc_dbg( 40, _CLIENT_BLOCK, __FILE__, __LINE__ );
	strcpy( p1, "p1 points to a Normal allocation block" );
	strcpy( p2, "p2 points to a Client allocation block" );
	
	/*
	* _free_dbg must be called to free the CLIENT block
	*/
	_free_dbg( p2, _CLIENT_BLOCK );
	free( p1 );
	
	/*
	* Allocate p1 again and then exit - this will leave unfreed
	* memory on the heap
	*/
	p1 = (char*)malloc( 10 );
}

