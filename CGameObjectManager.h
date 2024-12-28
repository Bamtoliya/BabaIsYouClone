#pragma once
#include "Blocks.h"
class CGameObjectManager
{
public:
	CGameObjectManager() {};
	~CGameObjectManager() { Release(); }

	static CGameObjectManager* GetInstance()
	{
		if (!m_pInstance) m_pInstance = new CGameObjectManager;
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

	//list<CGameObject*> GetPlayer() { return m_list[OBJID::Player]; }
	CGameObject* GetTarget(OBJID eID, CGameObject* pDst);
public:
	void		AddObject(OBJID eID, CGameObject* pObj);
	int			Update();
	void		LateUpdate();
	void		Render(Graphics* g);
	void		Render(HDC hDC);
	void		Release();
	//void		DeleteID(OBJID eID);
private:
	static CGameObjectManager* m_pInstance;
	list<CGameObject*> m_list[OBJID::END];
};

