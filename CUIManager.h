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
	list<CUIElement*> GetList()
	{
		return m_UIList;
	}
	void AddUIElement(CUIElement* ui)
	{
		m_UIList.push_back(ui);
	}
	void Update();
	void LateUpdate();
	void Release();
	void Render(Graphics* graphic);
	void Clear();
	
	void GameStart();
	void EnterTest();
	void EnterEdit();
	void Exit();
	
	
	void LoadMainMenuUI();
	void LoadGameUI();
	void MainMenu();
	void InGame();
	void Edit();

	void OpenInventory();
	void CloseInventory();
	void PauseMenu();
	void TestGame();
	void SetSceneID(SCENEID id);

	
private:
	static CUIManager* m_pInstance;
	list<CUIElement*> m_UIList;
	SCENEID m_eSceneID;
};

