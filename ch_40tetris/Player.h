// Player.h: interface for the CPlayer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _PLAYER_H_
#define _PLAYER_H_

class CPlayer  
{
protected:
	int		m_nX;
	int		m_nY;
	
	// Player Handle Block Pointer
	CBlock**	m_pBlock;

public:

	enum
	{
		START_X=10,
		START_Y=2,
		PLAYER_BLOCK_NUM=4
	};

	CPlayer();
	virtual ~CPlayer();

	//
	int Init();
	void Destroy();

	//
	void OffSet(int nX, int nY);

	int GetLeft();
	int GetRight();
	int GetBottom();

	//
	void SetBlock(CBlock** pBlock);
	CBlock** GetBlock();
	
	//
	int Update();

};

#endif





















