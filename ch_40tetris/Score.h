// Score.h: interface for the CScore class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _SCORE_H_
#define _SCORE_H_

struct sScore
{
	char m_szName[10];
	long  m_lScore;
};

class CScore
{
protected:
	sScore *m_pPlayerScore;
	sScore *m_pScoreList;

public:
	CScore();
	virtual ~CScore();

	enum
	{
		eMAX_SCORE_NUM=10
	};

	//
	int Init();
	void Destroy();

	//
	void AddScore(int nBlock=-1);

	//
	long GetScore(int nNum=-1);
	const char* GetName(int nNum=-1);

	//
	void SetName(const char* szName="noName");

	//
	void ClearScore()
	{
		m_pPlayerScore->m_lScore=0;
		SetName();
	}

	//
	int SaveScore();
};

#endif