// Score.cpp: implementation of the CScore class.
//
//////////////////////////////////////////////////////////////////////

#include "_stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScore::CScore()
{
	m_pPlayerScore=NULL;
	m_pScoreList=NULL;
}

CScore::~CScore()
{
	Destroy();
}

int CScore::Init()
{
	//
	m_pPlayerScore = new sScore;

	m_pPlayerScore->m_lScore=0;
	SetName();

	//
	m_pScoreList = new sScore [eMAX_SCORE_NUM];
	
	ZeroMemory(m_pScoreList, sizeof(sScore)*eMAX_SCORE_NUM);

	// 스코어 파일을 읽는다.

	FILE* fScore=NULL;

	fScore = fopen("SCORE.dat", "rb");

	if(fScore != NULL)
	{
		fread(m_pScoreList, sizeof(sScore)*eMAX_SCORE_NUM, 1, fScore);
		fclose(fScore);
	}

	return 1;
}

void CScore::Destroy()
{
	SAFE_DELETE(m_pPlayerScore);
	SAFE_DELETE_ARRAY(m_pScoreList);
}

void CScore::AddScore(int nBlock/* =-1 */)
{
	if(nBlock == -1)
	{
		m_pPlayerScore->m_lScore+=10;
	}
	else
	{
		int nMultiple=(int)(nBlock/g_pApp->m_pStage->GetWidth());
		m_pPlayerScore->m_lScore+=(nBlock*100)*nMultiple;
	}
}

long CScore::GetScore(int nNum/* =-1 */)
{
	if(nNum == -1)
	{
		return m_pPlayerScore->m_lScore;
	}
	// else
	return m_pScoreList[nNum].m_lScore;
}

const char* CScore::GetName(int nNum/* =-1 */)
{
	if(nNum == -1)
	{
		return m_pPlayerScore->m_szName;
	}
	// else
	return m_pScoreList[nNum].m_szName;
}

void CScore::SetName(const char* szName/* ="noName" */)
{
	strcpy(m_pPlayerScore->m_szName, szName);
}

int CScore::SaveScore()
{
	int nNum=11;
	sScore tmpScore;
	ZeroMemory(&tmpScore, sizeof(sScore));

	bool bSort=false;
	int i=0, j=0;
	for(i=0; i<eMAX_SCORE_NUM; ++i)
	{
		if(m_pScoreList[i].m_lScore < m_pPlayerScore->m_lScore)
		{
			nNum=i+1;
			memcpy(&tmpScore, &m_pScoreList[i], sizeof(sScore));
			memcpy(&m_pScoreList[i], m_pPlayerScore, sizeof(sScore));
			bSort=true;
			break;
		}
	}
	if(bSort)
	{
		for(i=0; i<eMAX_SCORE_NUM; ++i)
		{
			if(m_pScoreList[i].m_lScore < tmpScore.m_lScore)
			{
				sScore tmpScore2;
				memcpy(&tmpScore2, &m_pScoreList[i], sizeof(sScore));
				memcpy(&m_pScoreList[i], &tmpScore, sizeof(sScore));
				memcpy(&tmpScore, &tmpScore2, sizeof(sScore));
			}
		}
	}

	FILE* fScore=NULL;

	fScore=fopen("SCORE.dat", "wb");

	fwrite(m_pScoreList, sizeof(sScore)*eMAX_SCORE_NUM, 1, fScore);

	fclose(fScore);

	return nNum;
}