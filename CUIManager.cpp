#include "pch.h"
#include "Designs.h"
#include "UIElements.h"


CUIManager* CUIManager::m_pInstance = nullptr;

void CUIManager::Clear()
{
	for_each(m_UIList.begin(), m_UIList.end(), SafeDelete<CUIElement*>);
	m_UIList.clear();
}

void CUIManager::GameStart() { CSceneManager::GetInstance()->SetScene(SCENEID::Game); }
void CUIManager::EnterTest() { CSceneManager::GetInstance()->SetScene(SCENEID::Test); }
void CUIManager::EnterEdit() { CSceneManager::GetInstance()->SetScene(SCENEID::Test); }
void CUIManager::Exit()
{
	PostQuitMessage(0);
	return;
}
void CUIManager::Update()
{
	for (auto& e : m_UIList) { e->Update(); }
	switch (m_eSceneID)
	{
	case SCENEID::Menu:
		MainMenu();
		break;
	case SCENEID::Game:
		InGame();
		break;
	case SCENEID::Test:
		TestGame();
		break;
	case SCENEID::Edit:
		Edit();
		break;
	case SCENEID::End:
		break;
	default:
		break;
	}
}
void CUIManager::LateUpdate()
{
	
}
void CUIManager::Release()
{
	for_each(m_UIList.begin(), m_UIList.end(), SafeDelete<CUIElement*>);
	m_UIList.clear();
}
void CUIManager::Render(Graphics* graphic)
{
	for (auto& e : m_UIList)
	{
		e->Render(graphic);
	}
}
void CUIManager::Render(HDC hDC)
{
	for (auto& e : m_UIList)
	{
		e->Render(hDC);
	}
}
void CUIManager::LoadMainMenuUI()
{
}

void CUIManager::LoadGameUI()
{
}

void CUIManager::LoadEditUI()
{
	m_UIList.push_back(new CBlocksPanel(0, 0, OCX, 72, L"BlocksPanel", nullptr, true));
	/*m_UIList.push_back(new CPanel(0, 0, OCX, 80, L"Panel", nullptr, true));
	m_UIList.push_back(new CPanel(OCX-130, 0, 130, OCY, L"Panel", nullptr, true));*/
}

void CUIManager::SetSceneID(SCENEID id)
{
	Clear();
	m_eSceneID = id;
	switch (id)
	{
	case SCENEID::Menu:
		LoadMainMenuUI();
		break;
	case SCENEID::Game:
		LoadGameUI();
		break;
	case SCENEID::Test:
		LoadGameUI();
		break;
	case SCENEID::Edit:
		LoadEditUI();
		break;
	case SCENEID::End:
		break;
	default:
		break;
	}
}

void CUIManager::MainMenu()
{

}

void CUIManager::InGame()
{

}

void CUIManager::Edit()
{
	if (CKeyManager::GetInstance()->KeyDown(VK_TAB))
	{

	}
}

void CUIManager::PauseMenu()
{

}

void CUIManager::TestGame()
{

}