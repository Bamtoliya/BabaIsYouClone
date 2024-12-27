#pragma once
#include "Define.h"
class CKeyManager
{
private:
	CKeyManager();
	~CKeyManager();

public:
	bool		KeyPressing(int _iKey);
	bool		KeyDown(int _iKey);		// µü ÇÑ ¹ø ´­·¶À» ¶§
	bool		KeyUp(int _iKey);			// ´­·¶´Ù°¡ ¶ÃÀ» ¶§
	void		Update();
	void		LateUpdate();
public:
	static CKeyManager* GetInstance()
	{
		if (!m_pInstance) m_pInstance = new CKeyManager;
		return m_pInstance;
	}

	static void	DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static	CKeyManager* m_pInstance;
	bool	m_bKeyState[VK_MAX];
};

