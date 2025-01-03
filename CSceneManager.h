#pragma once
#include "Scenes.h"
class CScene;
class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	static CSceneManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSceneManager;

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

	SCENEID GetCurrentScene() { return m_eCurScene; }
	void SetScene(SCENEID eID);
	void SetStage(STAGEID eID);
	void Update();
	void LateUpdate();
	void Render(Graphics* g);
	void Render(HDC hDC);
	void Release();

private:
	static CSceneManager*	m_pInstance;
	CScene* m_pScene;

	bool m_bInStage;
	bool m_bInWorldMap;
	bool m_bPauseMenu;
	SCENEID				m_eCurScene;
	SCENEID				m_ePreScene;
};

