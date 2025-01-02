#pragma once
#include "CUIElement.h"
class CUIManager
{
public:
	static CUIManager* GetInstance()
	{
		if (!m_pInstance) m_pInstance = new CUIManager;
		return m_pInstance;
	}
	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
	vector<CUIElement*> GetVector()
	{
		return m_UIVector;
	}
	void AddUIElement(CUIElement* ui)
	{
		m_UIVector.push_back(ui);
	}
	void Update();
	void LateUpdate();
	void Release();
	void Render(Graphics* graphic);
	void Render(HDC hDC);
	void Clear();
	
	void GameStart();
	void EnterTest();
	void EnterEdit();
	void Exit();
	
	
	void LoadMainMenuUI();
	void LoadGameUI();
	void LoadEditUI();
	void MainMenu();
	void InGame();
	void Edit();

	void PauseMenu();
	void TestGame();
	void SetSceneID(SCENEID id);

	
private:
	CUIManager(): m_eSceneID(SCENEID::Menu) {}
	~CUIManager() {}
	static CUIManager* m_pInstance;
	vector<CUIElement*> m_UIVector;
	SCENEID m_eSceneID;
};

