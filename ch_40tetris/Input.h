// Input.h: interface for the CInput class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _INPUT_H_
#define _INPUT_H_

class CInput  
{
protected:
	bool m_bBuff;

	BYTE* m_pCurKey;
	BYTE* m_pOldKey;

	enum {MAX_KEY=256};

public:
	CInput();
	virtual ~CInput();

	//
	int Init(bool bBuff=true);
	void Destroy();

	//
	bool GetKey(int nVKey);
	bool GetKeyState(int nVKey);

	int Update();
};

#endif