
#pragma comment(lib, "dbghelp.lib")

#include <windows.h>
#include <dbgHelp.h>


//typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)(HANDLE hProcess, DWORD dwPid, ...);
//
//LONG ExceptionWrite(LPEXCEPTION_POINTERS pExp)
//{
//
//	LONG retval= EXCEPTION_CONTINUE_SEARCH;
//
//	HMODULE hDll= ::LoadLibrary(_T("DbgHelp.dll"));
//	MINIDUMPWRITEDUMP pDump= (MINIDUMPWRITEDUMP)::GetProcAddress(hDll, "MiniDumpWriteDump");
//	HANDLE hFile= ::CreateFile(_T("Crash.dmp"), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
//
//	_MINIDUMP_EXCEPTION_INFORMATION ExInfo;
//	ExInfo.ThreadId= ::GetCurrentThreadId();
//	ExInfo.ExceptionPointers= pExp;
//	ExInfo.ClientPointers= NULL;
//
//	BOOL hr= pDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL);
//
//	::CloseHandle(hFile);
//	::FreeLibrary(hDll);
//
//	return retval;
//}


LONG ExceptionWrite(LPEXCEPTION_POINTERS pExp)
{
	_MINIDUMP_EXCEPTION_INFORMATION ExInfo =
	{
		::GetCurrentThreadId()
		,	pExp
		,	NULL
	};

	HANDLE	hFile= ::CreateFile( "minidump.dmp", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
	BOOL	hr	 = ::MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL);

	::CloseHandle(hFile);

	return EXCEPTION_EXECUTE_HANDLER;
}


void main()
{
	::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ExceptionWrite);

	char* p = NULL;

	p[1] = 'T';
}


