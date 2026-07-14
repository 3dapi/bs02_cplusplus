#include "_stdafx.h"

#define IF_ROTATE_BLOCK(b, n)														\
	if(tmp.X == m_nRightRotateTrg[n][0] && tmp.Y == m_nRightRotateTrg[n][1])		\
	{																				\
		nRet = CheckCrashBlock(&b, m_nRightRotate[n][0], m_nRightRotate[n][1]);		\
		b.OffSet(m_nRightRotate[n][0], m_nRightRotate[n][1]);						\
	}

#define CASE_BLOCK_SETPOS(n, c, b)	\
	case n:					\
		pBlock[0]->SetPos(m_nFigure[n][0]+m_pPlayer->START_X, m_nFigure[n][1]+m_pPlayer->START_Y);	\
		pBlock[1]->SetPos(m_nFigure[n][2]+m_pPlayer->START_X, m_nFigure[n][3]+m_pPlayer->START_Y);	\
		pBlock[2]->SetPos(m_nFigure[n][4]+m_pPlayer->START_X, m_nFigure[n][5]+m_pPlayer->START_Y);	\
		pBlock[3]->SetPos(m_nFigure[n][6]+m_pPlayer->START_X, m_nFigure[n][7]+m_pPlayer->START_Y);	\
		pBlock[0]->SetColor(c,b);																		\
		pBlock[1]->SetColor(c,b);																		\
		pBlock[2]->SetColor(c,b);																		\
		pBlock[3]->SetColor(c,b);																		\
		break;

#define SET_BLOCKARY_BLOCK(b, n)	\
	m_BlockArr[b[n]->GetY()][b[n]->GetX()/2] = b[n]

#define SET_BLOCKARY_NULL(b, n)	\
	m_BlockArr[b[n]->GetY()][b[n]->GetX()/2] = NULL

CStage::CStage()
{
	m_nStageWidth = 0;
	m_nStageHeight = 0;
	m_nX = 0;
	m_nY = 0;
	m_BlockArr = NULL;

	m_lClock = 0;
	m_lOldClock = 0;

	m_pPlayer = NULL;
}

CStage::~CStage()
{
	Destroy();
}

//////////////////////////////////////////////////////////////////////////
int CStage::DelLine()
{
	// 줄삭제 검사
	int nBlockScore=0;
	int nBlock = 0;
	for(int j=DELAY_AREA; j<m_nStageHeight; ++j)
	{
		//
		nBlock = 0;

		int nTmp=0;

		//
		for(int i=0; i<m_nWidth; ++i)
		{
			++nTmp;
			if(m_BlockArr[j][i] != NULL)
			{
				++nBlock;
			}

			if(nTmp < nBlock)
			{
				break;
			}
		}

		//
		if(nBlock == m_nWidth)
		{
			for(int i=0;i<m_nWidth;++i)
			{
				CBlock** pBlock=m_pPlayer->GetBlock();
				for(int i=0; i<m_pPlayer->PLAYER_BLOCK_NUM; ++i)
				{
					if(pBlock[i] != NULL)
					{
						if(m_BlockArr[j][i]->GetX() == pBlock[i]->GetX() || m_BlockArr[j][i]->GetY() == pBlock[i]->GetY())
						{
							pBlock[i]=NULL;
						}
					}
				}

				SAFE_DELETE(m_BlockArr[j][i]);
				++nBlockScore;
			}

			// 줄 내림
			CBlock** pBlock = NULL;
			pBlock = new CBlock* [m_nWidth];

			for(i=0; i<m_nWidth; ++i)
			{
				pBlock[i] = NULL;
			}

			//
			for(int y=j; y>DELAY_AREA; --y)
			{
				for(int x=0; x<m_nWidth; ++x)
				{
					m_BlockArr[y][x] = m_BlockArr[y-1][x];

					if(m_BlockArr[y][x] != NULL)
					{
						m_BlockArr[y][x]->OffSet(0, 1);
					}
				}
			}
			SAFE_DELETE_ARRAY(pBlock);

			//
			Draw();
		}
	}

	g_pApp->m_pScore->AddScore(nBlockScore);

	return 1;
}

int CStage::OverCheck()
{
	/*
	for(int j=0; j<DELAY_AREA; ++j)
	{
		for(int i=0; i<m_nWidth; ++i)
		{
			if(m_BlockArr[j][i] != NULL)
			{
				int nCurY=m_BlockArr[j][i]->GetY();
				if(nCurY < 4)
				{
					return -1;
				}
			}
		}
	}
	*/

	CBlock** pBlock=m_pPlayer->GetBlock();

	// 게임오버 검사
	for(int i=0; i<m_pPlayer->PLAYER_BLOCK_NUM; ++i)
	{
		if(pBlock[i] != NULL)
		{
			int nCurY=pBlock[i]->GetY();
			if(nCurY < 4)
			{
				return -1;
			}
		}
	}

	return 1;
}

int CStage::Rotate()
{
	int i=0;

	CBlock** pBlock = m_pPlayer->GetBlock();
	
	CBlock TmpBlock[4];
	bool bSafe=true;

	// 회전 위치가 안전한지 미리 검사한다.
	for(i=0; i<m_pPlayer->PLAYER_BLOCK_NUM; ++i)
	{
		// 복사
		TmpBlock[i].Init(*pBlock[i]);
	}

	for(i=0; i<m_pPlayer->PLAYER_BLOCK_NUM; ++i)
	{
		int nRet=1;

		COORD tmp = TmpBlock[i] - TmpBlock[1];

		IF_ROTATE_BLOCK(TmpBlock[i], 1);
		IF_ROTATE_BLOCK(TmpBlock[i], 2);
		IF_ROTATE_BLOCK(TmpBlock[i], 3);
		IF_ROTATE_BLOCK(TmpBlock[i], 5);
		IF_ROTATE_BLOCK(TmpBlock[i], 6);
		IF_ROTATE_BLOCK(TmpBlock[i], 7);
		IF_ROTATE_BLOCK(TmpBlock[i], 9);
		IF_ROTATE_BLOCK(TmpBlock[i], 10);
		IF_ROTATE_BLOCK(TmpBlock[i], 11);

		IF_ROTATE_BLOCK(TmpBlock[i], 0);
		IF_ROTATE_BLOCK(TmpBlock[i], 4);
		IF_ROTATE_BLOCK(TmpBlock[i], 8);
		IF_ROTATE_BLOCK(TmpBlock[i], 12);

		if(nRet != 1)
		{
			bSafe=false;
		}
	}

	//
	if(bSafe)
	{
		for(i=0; i<m_pPlayer->PLAYER_BLOCK_NUM; ++i)
		{
			SET_BLOCKARY_NULL(pBlock, i);
		}
		for(i=0; i<m_pPlayer->PLAYER_BLOCK_NUM; ++i)
		{
			pBlock[i]->Init(TmpBlock[i]);
			SET_BLOCKARY_BLOCK(pBlock, i);
		}
	}

	return 1;
}

int CStage::CheckCrashBlock(CBlock* pBlock, int nX, int nY, bool bPlayer/*=true*/)
{
	int nCurX=pBlock->GetX();
	int nCurY=pBlock->GetY();

	bool bMove=true;

	// 바닥 충돌 체크
	if (nCurY+nY>=m_nHeight+m_nY+DELAY_AREA)
	{
		return -1;
	}

	// 이동하고자 하는 곳에 블럭이 있는지 확인한다.
	CBlock *pTrgBlock=NULL;

	//|| (nCurX+nX+m_nX)/2 < 0
	if(nCurY+nY < 0) return 0;
	
	pTrgBlock=m_BlockArr[nCurY+nY][(nCurX+nX)/2];

	if(pTrgBlock != NULL)
	{
		bool bOverlap=false;

		// Player Block인지 검사
		if(bPlayer)
		{
			CBlock** pPlayer=m_pPlayer->GetBlock();

			for(int i=0;i<m_pPlayer->PLAYER_BLOCK_NUM; ++i)
			{
				if(pTrgBlock == pPlayer[i])
				{
					bOverlap = true;
				}
			}
		}

		if(nX==0 && nY==1 && !bOverlap)
		{
			return -1;
		}

		bMove=bOverlap;
	}

	// 좌, 우 벽 충돌 체크
	if(((nCurX+nX<0)&&nX<0) || ((nCurX+nX>=m_nWidth*2)&&nX>0))
	{
		bMove=false;
	}

	//
	if(!bMove)
	{
		return 0;
	}

	return 1;
}

int CStage::CheckCrash(int nX, int nY)
{


	CBlock** pBlock = m_pPlayer->GetBlock();

	int nRet=0;
	for(int i=0; i<m_pPlayer->PLAYER_BLOCK_NUM; ++i)
	{
		nRet=CheckCrashBlock(pBlock[i], nX, nY);
		if(nRet == -1)
		{
			return -1;
		}
		else if(nRet == 0)
		{
			return 0;
		}
	}

	return 1;
}

void CStage::OffsetPlayer(int nX, int nY, bool bLoop/*=false*/)
{
	//  점수 계산
	if(nY == +1)
	{
		g_pApp->m_pScore->AddScore();
	}

	//
	int nLeft = m_pPlayer->GetLeft();
	int nRight = m_pPlayer->GetRight();
	int nBottom = m_pPlayer->GetBottom();

	int nRet=0;
	if(m_pPlayer != NULL)
	{
		do
		{
			// 충돌 체크
			nRet = CheckCrash(nX, nY);
			if(nRet == -1 )
			{
				DelLine();
				if(OverCheck() == -1)
				{
					g_pApp->m_bRun=false;
					return;
				}

				CreateFigure();

				return;
			}
			else if(nRet == 0)
			{
				return;
			}

			////
			// 데이터 이동
			CBlock** pBlock = NULL;

			pBlock = m_pPlayer->GetBlock();

			SET_BLOCKARY_NULL(pBlock, 0);
			SET_BLOCKARY_NULL(pBlock, 1);
			SET_BLOCKARY_NULL(pBlock, 2);
			SET_BLOCKARY_NULL(pBlock, 3);

			m_pPlayer->OffSet(nX,nY);

			SET_BLOCKARY_BLOCK(pBlock, 0);
			SET_BLOCKARY_BLOCK(pBlock, 1);
			SET_BLOCKARY_BLOCK(pBlock, 2);
			SET_BLOCKARY_BLOCK(pBlock, 3);
		}
		while(bLoop);
	}
}

int CStage::Update()
{
	m_lClock = clock();

	long lCurClock = (m_lClock>m_lOldClock)? m_lClock-m_lOldClock: m_lOldClock-m_lClock;

	if ( lCurClock < DOWN_DELAY )
	{
		return -1;
	}

	OffsetPlayer(0, +1);
	
	m_lClock = m_lOldClock = clock();
	
	return 1;
}

void CStage::CreateFigure(CBlock** pBlock)
{
	pBlock[0] = new CBlock;
	pBlock[1] = new CBlock;
	pBlock[2] = new CBlock;
	pBlock[3] = new CBlock;

	pBlock[0]->Init();
	pBlock[1]->Init();
	pBlock[2]->Init();
	pBlock[3]->Init();
	
	int nFigure = rand() % 7;
	switch(nFigure)
	{
		// 막대기
		CASE_BLOCK_SETPOS(0, CBlock::CR_NULL, CBlock::CR_WHITE);
		// 기억 정방향
		CASE_BLOCK_SETPOS(1, CBlock::CR_NULL, CBlock::CR_IBLUE);
		// 기억 역방향
		CASE_BLOCK_SETPOS(2, CBlock::CR_NULL, CBlock::CR_IBLUEGREEN);
		// ㄴ+ㄱ 정방향
		CASE_BLOCK_SETPOS(3, CBlock::CR_NULL, CBlock::CR_IGREEN);
		// ㄴ+ㄱ 역방향
		CASE_BLOCK_SETPOS(4, CBlock::CR_NULL, CBlock::CR_GREEN);
		// 삼각 정방향
		CASE_BLOCK_SETPOS(5, CBlock::CR_NULL, CBlock::CR_IYELLOW);
		// 삼각 역방향
		CASE_BLOCK_SETPOS(6, CBlock::CR_NULL, CBlock::CR_YELLOW);
	}
}

void CStage::CreateFigure()
{
	m_pPlayer->SetBlock(m_pPlayer2->GetBlock());
	CreateFigure(m_pPlayer2->GetBlock());
	SetBlockArray(m_pPlayer->GetBlock());
}

void CStage::SetBlockArray(CBlock** pBlock)
{
	SET_BLOCKARY_BLOCK(pBlock, 0);
	SET_BLOCKARY_BLOCK(pBlock, 1);
	SET_BLOCKARY_BLOCK(pBlock, 2);
	SET_BLOCKARY_BLOCK(pBlock, 3);
}

int CStage::Init(int nX/* =4 */, int nY/* =0 */, int nWidth/* =11 */, int nHeight/* =19 */)
{
	int i=0, j=0;

	//
	m_nStageWidth = nWidth;
	m_nStageHeight = nHeight+DELAY_AREA;


	m_nWidth = nWidth;
	m_nHeight = nHeight;

	m_nX = nX;
	m_nY = nY;

	//
	m_BlockArr = new CBlock** [m_nStageHeight];

	for(i=0;i<m_nStageHeight;++i)
	{
		m_BlockArr[i] = new CBlock* [m_nStageWidth];
	}

	//
	for(j=0;j<m_nStageHeight;++j)
	{
		for(i=0;i<m_nStageWidth;++i)
		{
			m_BlockArr[j][i] = NULL;
		}
	}

	//
	FILE* hFile=NULL;
	hFile = fopen("Tetris.dat", "rb");
	if (hFile==NULL)
	{
		return -1;
	}
	fread(m_nFigure, sizeof(int)*7*8, 1, hFile);
	fread(m_nRightRotate, sizeof(int)*13*2, 1, hFile);
	fread(m_nRightRotateTrg, sizeof(int)*13*2, 1, hFile);
	fclose(hFile);

	//
	tm time;
	_getsystime(&time);
	srand(time.tm_sec);

	m_lClock = clock();

	//
	m_pPlayer = new CPlayer;
	m_pPlayer->Init();

	m_pPlayer2 = new CPlayer;
	m_pPlayer2->Init();

	return 1;
}

void CStage::Destroy()
{
	int i=0, j=0;

	for(i=0;i<m_nStageHeight; ++i)
	{
		for(j=0;j<m_nStageWidth; ++j)
		{
			SAFE_DELETE(m_BlockArr[i][j]);
		}
		SAFE_DELETE_ARRAY(m_BlockArr[i]);
	}
	SAFE_DELETE_ARRAY(m_BlockArr);

	CBlock** pBlock=m_pPlayer2->GetBlock();
	for(i=0;i<m_pPlayer->PLAYER_BLOCK_NUM; ++i)
	{
		SAFE_DELETE(pBlock[i]);
	}
	SAFE_DELETE_ARRAY(pBlock);

	SAFE_DELETE(m_pPlayer);
}

using std::cout;
void CStage::Draw()
{
	CConsole *screen = g_pApp->m_pConsole;

	// Draw Block
	for(int j=0;j<m_nStageHeight;++j)
	{
		for(int i=0;i<m_nStageWidth;++i)
		{
			if(m_BlockArr[j][i] != NULL)
			{
				screen->SetTextColor(m_BlockArr[j][i]->GetColor());
				screen->Print(m_BlockArr[j][i]->GetX()+m_nX, m_BlockArr[j][i]->GetY(), m_BlockArr[j][i]->GetChar());
			}
			else
			{
				screen->SetTextColor(screen->CR_NULL, screen->CR_NULL);
				screen->Print(m_nX+i*2, j, "  ");
			}
		}
	}

	// 벽 그리기
	screen->SetTextColor(screen->CR_NULL,screen->CR_IWHITE);
	for(int i=DELAY_AREA;i<m_nStageHeight;++i)
	{
		screen->Print(m_nX-2,i, "▒");
		screen->Print(m_nX+m_nWidth*2,i, "▒");
	}
	for(i=0; i<m_nWidth+2;++i)
	{
		screen->SetCursor(m_nX-2 + i*2, m_nStageHeight);screen->Print("▒");
	}

	// 2번재 블럭 그림
	int nX=25;
	int nY=3;
	for(i=0;i<4;++i)
	{
		screen->SetTextColor();
		screen->Print(nX+8, nY+i, "          ");
	}

	CBlock** pBlock = m_pPlayer2->GetBlock();
	for(i=0; i<m_pPlayer->PLAYER_BLOCK_NUM; ++i)
	{
		screen->SetTextColor(pBlock[i]->GetColor());
		screen->Print(nX+pBlock[i]->GetX(), nY+pBlock[i]->GetY(), pBlock[i]->GetChar());
	}

//#define _TETRIS_VIEW
#ifdef _TETRIS_VIEW
	// 더미
	nX=50;
	nY=0;
	int nCount=0;

	for(j=0;j<m_nStageHeight;++j)
	{
		for(int i=0;i<m_nStageWidth;++i)
		{
			if(m_BlockArr[j][i] != NULL)
			{
				screen->SetTextColor(m_BlockArr[j][i]->GetColor());
				++nCount;
			}
			else
			{
				screen->SetTextColor(screen->CR_NULL, screen->CR_INTENSE);
			}
			screen->Print(nX+i*2, j, "  ");
		}
	}

	screen->Print(0, DELAY_AREA, "->");

	screen->SetTextColor();
	pBlock = m_pPlayer->GetBlock();
	for(i=0;i<m_pPlayer->PLAYER_BLOCK_NUM; ++i)
	{
		if(pBlock[i] != NULL)
		{
			screen->Print(30, i, "%d->X:%d,Y:%d(%d,%d)", i, pBlock[i]->GetX(), pBlock[i]->GetY(), pBlock[i]->GetX()/2, pBlock[i]->GetY());
		}
	}
	screen->Print(30, 4, "Count Block Num : %d", nCount);
#endif

}