#include "pch.h"
#include "Designs.h"
#include "UIElements.h"


CUIManager* CUIManager::m_pInstance = nullptr;

void CUIManager::Clear()
{
	for_each(m_UIVector.begin(), m_UIVector.end(), SafeDelete<CUIElement*>);
	m_UIVector.clear();
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
	for_each(m_UIVector.begin(), m_UIVector.end(), SafeDelete<CUIElement*>);
	m_UIVector.clear();
}
void CUIManager::Render(Graphics* graphic)
{
	for (auto& e : m_UIVector)
	{
		e->Render(graphic);
	}
}
void CUIManager::Render(HDC hDC)
{
	for (auto& e : m_UIVector)
	{
		e->Render(hDC);
	}
}
void CUIManager::LoadMainMenuUI()
{
	m_UIVector.push_back(new CMainMenuUI);
}

void CUIManager::LoadGameUI()
{
	
}

void CUIManager::LoadEditUI()
{
	m_UIVector.push_back(new CBlocksPanel(0, 0, OCX, 72, L"BlocksPanel", nullptr, true));
	m_UIVector.push_back(new CButton(600, OCY-100, 200, 40, L"RETURN", nullptr, true));
}

void CUIManager::SetSceneID(SCENEID id)
{
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
	for (auto& e : m_UIVector)
	{ 
		if (m_UIVector != CUIManager::GetInstance()->m_UIVector)
			break;
		else
			e->Update();
	}
	
}

void CUIManager::InGame()
{
	for (auto& e : m_UIVector)
	{
		if (m_UIVector != CUIManager::GetInstance()->m_UIVector)
			break;
		else 
			e->Update(); 
	}
}

void CUIManager::Edit()
{
	for (auto& e : m_UIVector)
	{ 
		if (m_UIVector != CUIManager::GetInstance()->m_UIVector)
			break;
		else 
			e->Update(); 
	}
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