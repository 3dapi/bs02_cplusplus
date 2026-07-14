#include "_stdafx.h"

//////////////////////////////////////////////////////////////////////////
// 생성자
CConsole::CConsole()
{
	m_hConsole = NULL;
	m_Cursor.X = 0;
	m_Cursor.Y = 0;

	m_nWidth = 0;
	m_nHeight = 0;
}

//////////////////////////////////////////////////////////////////////////
// 소멸자
CConsole::~CConsole()
{
	Destroy();
}

//////////////////////////////////////////////////////////////////////////
// 맴버 함수
int CConsole::Init()
{
	BOOL bRet;

	m_hConsoleBack1=GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_hConsoleBack1 == INVALID_HANDLE_VALUE)
		return -1;

	m_hConsoleBack2=CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, 0);
	if(m_hConsoleBack2 == INVALID_HANDLE_VALUE)
		return -1;

	m_hConsole=m_hConsoleBack1;

	bRet=GetConsoleScreenBufferInfo(m_hConsoleBack2, &m_ConsoleInfo);
	if(!bRet) return FALSE;

	bRet=SetConsoleScreenBufferSize(m_hConsoleBack1, m_ConsoleInfo.dwSize);
	if(!bRet) return FALSE;

	bRet = GetConsoleCursorInfo(m_hConsoleBack1, &m_CursorInfo);
	if(!bRet) return FALSE;

	// BackBuffer 1
	bRet = SetCursor(0, 0);
	if(!bRet) return FALSE;

	bRet = SetCursorVisble(FALSE);
	if(!bRet) return FALSE;

	// BackBuffer 2
	Flip();
	bRet = SetCursor(0, 0);
	if(!bRet) return FALSE;

	bRet = SetCursorVisble(FALSE);
	if(!bRet) return FALSE;

	m_nWidth = m_ConsoleInfo.srWindow.Right - m_ConsoleInfo.srWindow.Left;
	m_nHeight = m_ConsoleInfo.srWindow.Bottom - m_ConsoleInfo.srWindow.Top;

	// Default BackBuffer
	m_hConsole = m_hConsoleBack2;

	return 1;
}

void CConsole::Destroy()
{
	m_hConsole = NULL;
	if(!m_CursorInfo.bVisible)
	{
		SetCursorVisble(TRUE);
	}
}


void CConsole::SetFront()
{
	m_hConsole=m_hConsoleBack2;
	Flip();
}

void CConsole::Flip()
{
	if(m_hConsole == m_hConsoleBack1)
	{
		m_hConsole=m_hConsoleBack2;
	}
	else
	{
		m_hConsole=m_hConsoleBack1;
	}
	SetConsoleActiveScreenBuffer(m_hConsole);
}

BOOL CConsole::Print(int nX, int nY, const char* szStr, ...)
{
	SetCursor(nX, nY);

	char szTmp[255];

	va_list	marker;
	va_start(marker, szStr);
	vsprintf(szTmp, szStr, marker);
	va_end(marker);

	Print(szTmp);

	return TRUE;
}


BOOL CConsole::Print(const char* szStr, ...)
{
	char szTmp[255];

	va_list	marker;
	va_start(marker, szStr);
	vsprintf(szTmp, szStr, marker);
	va_end(marker);

	DWORD nNum=0;

	int nLen=strlen(szTmp);
	WriteFile(m_hConsole, szTmp, nLen, &nNum, NULL);
	if(nLen != nNum)
		return FALSE;

	return TRUE;
}

BOOL CConsole::SetConsoleMode(DWORD dwMode)
{
	return ::SetConsoleMode(m_hConsole, dwMode);
}

void CConsole::FillConsole()
{
	unsigned long lNumLine;
	COORD tmp = {0, 0};
	FillConsoleOutputAttribute(m_hConsole, CR_NULL|(CR_NULL<<4), m_nWidth*m_nHeight, tmp, &lNumLine);

	/*
	SetTextColor();
	for(int j=0; j<m_nHeight; ++j)
	{
		for(int i=0; i<m_nWidth; ++i)
		{
			SetCursor(i, j);
			Print(" ");
		}
	}
	*/
}

// Cursor 보이기, 감춤
BOOL CConsole::SetCursorVisble(BOOL bView)
{
	m_CursorInfo.bVisible = bView;
	return SetConsoleCursorInfo(m_hConsole, &m_CursorInfo);
}

// Cursor 위치 조정
BOOL CConsole::SetCursor(int nX, int nY)
{
	m_Cursor.X = nX;
	m_Cursor.Y = nY;
	return SetCursor(m_Cursor);
}
BOOL CConsole::SetCursor(COORD Axis)
{
	return SetConsoleCursorPosition(m_hConsole, m_Cursor);
}

BOOL CConsole::SetTextColor(WORD wColor, WORD wBgColor /* = 0x0 */)
{
	return SetConsoleTextAttribute(m_hConsole, wColor | (wBgColor<<4));
}

BOOL CConsole::SetTextColor(void)
{
	return SetTextColor(CR_WHITE, CR_NULL);
}
