// App.h: interface for the CApp class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __APP_H__
#define __APP_H__

class CApp
{
public:
	CApp();
	virtual ~CApp();

	//
	int Init();
	void Destroy();

	//
	int Title();
	int Run();
	int GameOver();
	void EnterName();

	CInput*		m_pInput;
	CConsole*	m_pConsole;
	CStage*		m_pStage;
	CScore*		m_pScore;

	bool		m_bRun;
};

#endif //__APP_H__