#ifndef __BLOCK_H__
#define __BLOCK_H__
////
// CBlock (1 x 1)

class CBlock
{
public:
	CBlock();
	CBlock(const CBlock& Block);
	~CBlock();

	// Init
	int Init(int nX=0, int nY=0, WORD wColor=CR_NULL, WORD wBgColor=CR_IWHITE, char *szChar="  ", int nWidth=2, int nHeight=1);
	int Init(const CBlock& Block);
	void Destroy();

	// 좌표
	BOOL SetPos(int nX=0, int nY=0);
	COORD GetPos(void);

	int GetX() {return m_nX;}
	int GetY() {return m_nY;}

	void OffSet(int nX, int nY);

	//
	COORD operator-(const CBlock& p) const
	{
		COORD tmp;
		tmp.X = m_nX - p.m_nX;
		tmp.Y = m_nY - p.m_nY;

		return tmp;
	}
	
	//
	BOOL SetChar(char *szChar);
	char* GetChar(void);

	//
	void SetColor(WORD wColor, WORD wBgColor=CR_NULL);
	WORD GetColor(void);

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
	// Axis
	int m_nX;
	int m_nY;

	// Size
	int m_nWidth;
	int m_nHeight;

	// Block Character[m_nWidth]
	char *m_szChar;

	// Block Color
	WORD m_wColor;
private:
};
#endif //__BLOCK_H__