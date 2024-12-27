#pragma once
#include "CScene.h"
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
	void Update();
	void LateUpdate();
	void Render(Graphics* g);
	void Release();

private:
	static CSceneManager*	m_pInstance;
	CScene* m_pScene;

	SCENEID				m_eCurScene;
	SCENEID				m_ePreScene;
};

