// Input.cpp: implementation of the CInput class.
//
//////////////////////////////////////////////////////////////////////

#include "_stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInput::CInput()
{
	m_bBuff = TRUE;
	m_pCurKey = NULL;
	m_pOldKey = NULL;
}

CInput::~CInput()
{
	Destroy();
}

bool CInput::GetKey(int nVKey)
{
//	if(m_bBuff)
//	{
//		// GetKeyboardState
//		return (m_pCurKey[nVKey] & 0x80 && m_pOldKey[nVKey] != m_pCurKey[nVKey]);
//	}
//	else
//	{
//		// GetAsyncKeyState
//		return ((GetAsyncKeyState(nVKey) & 0x8000)?true:false);
//	}

	return (m_pCurKey[nVKey] && !m_pOldKey[nVKey]);

	return false;
}

bool CInput::GetKeyState(int nVKey)
{
	if(m_bBuff)
	{
		// GetKeyboardState
		return (m_pCurKey[nVKey] & 0x80 && true);
	}
	else
	{
		return ((GetAsyncKeyState(nVKey) & 0x8000)?true:false);
	}

	return false;
}

#define IF_GETKEYSTATE(vk)													\
	if( (GetAsyncKeyState(vk)&0x8000) ) m_pCurKey[vk] = 1;	\

int CInput::Update()
{
	if(m_bBuff)
	{
		memcpy(m_pOldKey, m_pCurKey, MAX_KEY*sizeof(unsigned char));
		memset(m_pCurKey, 0, MAX_KEY*sizeof(unsigned char));
		
		// GetAsyncKeyState
		for(int i=1;i<MAX_KEY;++i)
		{
			IF_GETKEYSTATE(i);
		}


//		BOOL bRet=GetKeyboardState(m_pCurKey);
//		
//		if(!bRet)
//		{
//			_ASSERT(0);
//		}
	}

return 1;
}

int CInput::Init(bool bBuff/* =true */)
{
	m_bBuff = bBuff;
	if(m_bBuff)
	{
		m_pCurKey = new unsigned char [MAX_KEY*sizeof(unsigned char)];
		m_pOldKey = new unsigned char [MAX_KEY*sizeof(unsigned char)];
		memset(m_pCurKey, 0, MAX_KEY*sizeof(unsigned char));
		memset(m_pOldKey, 0, MAX_KEY*sizeof(unsigned char));
	}

	Update();
	
	return 1;
}

void CInput::Destroy()
{
	SAFE_DELETE_ARRAY(m_pCurKey);
	SAFE_DELETE_ARRAY(m_pOldKey);
}
