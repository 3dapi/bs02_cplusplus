#include "_stdafx.h"

CApp* g_pApp;

////
// Console Width x Height : 79 x 24

void main()
{
	int nRet=0;
	bool bRun=true;

	g_pApp=new CApp;

	// Init
	nRet=g_pApp->Init();
	
	if(nRet<0)
	{
		return ;
	}

	// Title
	nRet=g_pApp->Title();
	if(nRet == -1)
	{
		bRun=false;
	}

	// Main Game
	while(bRun)
	{
		nRet=g_pApp->Run();
		if(nRet == -1 || nRet == 0)
		{
			if(nRet != 0)
			{
				g_pApp->EnterName();

				nRet=g_pApp->GameOver();
			}
			if(nRet==-1 || nRet==0)
			{
				bRun=false;
			}
		}

		// Àç½ÃÀÛ
		if(bRun!=false)
		{
			g_pApp->m_pStage->Destroy();
			g_pApp->m_pStage->Init();
		}
	}

	SAFE_DELETE(g_pApp);
}