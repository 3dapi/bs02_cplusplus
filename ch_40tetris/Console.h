#ifndef __CONSOLE_H__
#define __CONSOLE_H__
//////////////////////////////////////////////////////////////////////////
// 화면 관리 담당 Class : Console

class CConsole
{
public:
	CConsole();
	~CConsole();

	int m_nWidth;
	int m_nHeight;

	int Init();
	void Destroy();

	//
	BOOL SetCursorVisble(BOOL bView);
	BOOL SetCursor(int nX, int nY);
	BOOL SetCursor(COORD Axis);

	//BOOL SetTextBgColor(WORD wColor);
	BOOL SetTextColor(WORD wColor, WORD wBgColor = 0x0);
	BOOL SetTextColor(void);

	//
	BOOL Print(const char* szStr, ...);
	BOOL Print(int nX, int nY, const char* szStr, ...);

	//
	BOOL SetConsoleMode(DWORD dwMode);

	//
	void SetFront();

	//
	void FillConsole();

	//
	void Flip();

	enum
	{
		CR_NULL			= 0x0000,	// 검정 (기본 배경색)
		CR_BLUE			= 0x0001,	// 청색
		CR_GREEN		= 0x0002,	// 녹색
		CR_BLUEGREEN	= 0x0003,	// 청녹색
		CR_RED			= 0x0004,	// 적색
		CR_PURPLE		= 0x0005,	// 자색
		CR_YELLOW		= 0x0006,	// 노란색
		CR_WHITE		= 0x0007,	// 흰색	(기본 전경색)
		CR_INTENSE		= 0x0008,	// 반전색 (회색)

		CR_IBLUE		= 0x0009,	// 밝은 청색
		CR_IGREEN		= 0x000a,	// 밝은 녹색
		CR_IBLUEGREEN	= 0x000b,	// 밝은 청녹색 (하늘색)
		CR_IRED			= 0x000c,	// 밝은 적색
		CR_IPURPLE		= 0x000d,	// 밝은 자색
		CR_IYELLOW		= 0x000e,	// 밝은 노란색
		CR_IWHITE		= 0x000f	// 밝은 흰색
	};

protected:
	// Console Handle
	HANDLE	m_hConsole;
	HANDLE	m_hConsoleBack1;
	HANDLE	m_hConsoleBack2;

	CONSOLE_SCREEN_BUFFER_INFO	m_ConsoleInfo;
	CONSOLE_CURSOR_INFO			m_CursorInfo;

	// Cursor Position
	COORD	m_Cursor;

private:
};
#endif //__CONSOLE_H__