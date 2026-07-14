// Player.cpp: implementation of the CPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "_stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlayer::CPlayer()
{
	m_pBlock = NULL;
	m_nX = 0;
	m_nY = 0;
}

CPlayer::~CPlayer()
{
	Destroy();
}

int CPlayer::GetLeft()
{
	int nLeft=999;

	for(int i=0; i<PLAYER_BLOCK_NUM; ++i)
	{
		if(nLeft > m_pBlock[i]->GetX())
		{
			nLeft = m_pBlock[i]->GetX();
		}
	}
	return nLeft;
}

int CPlayer::GetRight()
{
	int nRight=0;

	for(int i=0; i<PLAYER_BLOCK_NUM; ++i)
	{
		if(nRight < m_pBlock[i]->GetX())
		{
			nRight = m_pBlock[i]->GetX();
		}
	}

	return nRight;
}

int CPlayer::GetBottom()
{
	int nBottom=0;
	for(int i=0;i<PLAYER_BLOCK_NUM; ++i)
	{
		if(nBottom < m_pBlock[i]->GetY())
		{
			nBottom = m_pBlock[i]->GetY();
		}
	}

	return nBottom;
}

void CPlayer::OffSet(int nX, int nY)
{
	m_nX += nX;
	m_nY += nY;

	m_pBlock[0]->OffSet(nX,nY);
	m_pBlock[1]->OffSet(nX,nY);
	m_pBlock[2]->OffSet(nX,nY);
	m_pBlock[3]->OffSet(nX,nY);
}

void CPlayer::SetBlock(CBlock** pBlock)
{
	m_nX = START_X;
	m_nY = START_Y;

	for(int i=0; i<PLAYER_BLOCK_NUM; ++i)
	{
		m_pBlock[i] = pBlock[i];
	}
}

CBlock** CPlayer::GetBlock()
{
	return m_pBlock;
}

int CPlayer::Init()
{
	m_nX = START_X;
	m_nY = START_Y;

	m_pBlock = new CBlock* [4];

	return 1;
}

void CPlayer::Destroy()
{
	SAFE_DELETE_ARRAY(m_pBlock);
}

int CPlayer::Update()
{
	
	return 1;
}
