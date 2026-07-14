//////////////////////////////////////////////////////////////////////////
// Stage Class

////
// Stage 위치 ( x, y )			: 화면에서 좌측 상단으로부터 어디에 그릴것인가.
// Stage 크기 ( Width, Height )	: 좌측, 우측, 하단의 벽을 제외한 스테이지 넓이
//								  실제 크기는 Width+2, Height+1 이 된다.

////
// Block
// 1 {{0, -2}, {0, -1}, {0, 0}, {0, +1}} : 막대기
// 2 {{0, -1}, {0, 0}, {0, +1}, {-2, +1}} : 기억 (정방향)
// 3 {{0, -1}, {0, 0}, {0, +1}, {+2, +1}} : 기억 (역방향)
// 4 {{0, -1}, {0, 0}, {-2, 0}, {-2, +1}} : (정방향)
// 5 {{0, -1}, {0, 0}, {+2, 0}, {+2, +1}} : (역방향)
// 6 {{0, -1}, {0, 0}, {-2, 0}, {0, +1}} : 삼각 (정방향)
// 7 {{0, -1}, {0, 0}, {+2, 0}, {0, +1}} : 삼각 (역방향)

#ifndef __STAGE_H__
#define __STAGE_H__

class CPlayer;
class CStage
{
public:
	CStage();
	~CStage();

	enum
	{
		DELAY_AREA	=	4,
		DOWN_DELAY	=	1000,
	};

	//
	int Init(int nX=4, int nY=0, int nWidth=11, int nHeight=19);
	void Destroy();

	//
	int GetWidth() {return m_nWidth;};

	//
	void CreateFigure();
	void CreateFigure(CBlock** pBlock);
	void SetBlockArray(CBlock** pBlock);
	void OffsetPlayer(int nX, int nY, bool bLoop=false);

	//
	int CheckCrash(int nX, int nY);
	int CheckCrashBlock(CBlock* pBlock, int nX, int nY, bool bPlayer=true);

	//
	int Rotate();

	int DelLine();

	//
	int OverCheck();

	//
	void Draw();

	//
	int Update();

public:
	CPlayer* m_pPlayer;
	CPlayer* m_pPlayer2;

protected:
	CBlock ***m_BlockArr;

	// 벽을 합한 크기
	int m_nStageWidth;
	int m_nStageHeight;

	// 본래 크기
	int m_nWidth;
	int m_nHeight;

	int m_nX;
	int m_nY;

	//
	long m_lClock;
	long m_lOldClock;

	int m_nFigure[7][8];
	int m_nRightRotate[13][2];
	int m_nRightRotateTrg[13][2];
private:
};
#endif //__STAGE_H__