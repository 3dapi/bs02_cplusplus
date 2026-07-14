#include "_stdafx.h"

CBlock::CBlock()
{
	m_nX = 0;
	m_nY = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_szChar = NULL;
}
CBlock::CBlock(const CBlock& Block)
{
	Init(Block);
}

CBlock::~CBlock()
{
	Destroy();
}

int CBlock::Init(int nX// =0 
				 , int nY// =0
				 , WORD wColor/* =CR_NULL */
				 , WORD wBgColor/* =CR_IWHITE */
				 , char *szChar/* ="  " */
				 , int nWidth/* =2 */
				 , int nHeight/* =1 */
				 )
{
	m_nX = nX;
	m_nY = nY;

	m_nWidth = nWidth;
	m_nHeight = nHeight;

	m_szChar = new char [nWidth+1];

	SetChar(szChar);

	SetColor(wColor, wBgColor);

	return 1;
}

int CBlock::Init(const CBlock& Block)
{
	m_nX=Block.m_nX;
	m_nY=Block.m_nY;
	m_nWidth=Block.m_nWidth;
	m_nHeight=Block.m_nHeight;
	SAFE_DELETE(m_szChar);
	m_szChar = new char [Block.m_nWidth+1];
	SetChar(Block.m_szChar);

	SetColor(Block.m_wColor);

	return 1;
}

void CBlock::Destroy()
{
	SAFE_DELETE_ARRAY(m_szChar);
}

BOOL CBlock::SetPos(int nX/* =0 */, int nY/* =0 */)
{
	m_nX = nX;
	m_nY = nY;

	return TRUE;
}

COORD CBlock::GetPos()
{
	COORD tmp = {m_nX, m_nY};
	return tmp;
}
void CBlock::OffSet(int nX, int nY)
{
	m_nX += nX;
	m_nY += nY;
}


// 넓이 만큼의 글자를 저장한다.
BOOL CBlock::SetChar(char *szChar)
{
	if ((int)strlen(szChar) > m_nWidth)
		return FALSE;

	strcpy(m_szChar, szChar);

	return TRUE;
}

char* CBlock::GetChar(void)
{
	return m_szChar;
}

void CBlock::SetColor(WORD wColor, WORD wBgColor/* =CR_NULL */)
{
	m_wColor = wColor | wBgColor<<4;
}

WORD CBlock::GetColor(void)
{
	return m_wColor;
}