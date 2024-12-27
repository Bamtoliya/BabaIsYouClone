#include "pch.h"
#include "CUIManager.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CButton.h"
#include "CPanel.h"
#include "CMenuButton.h"
#include "CInventoryPanel.h"
#include "CAudioManager.h"
#include "CBarPanel.h"
#include "CHPBar.h"
#include "CHUDPanel.h"
#include "CHotKeyPanel.h"

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

void CUIManager::LoadMainMenuUI()
{
	//UI ·»´õ¸µ
	m_UIList.push_back(new CMenuButton(b2Vec2(OCX * 0.5f, OCY * 0.5f), b2Vec2(50, 20), L"Start", true));
	m_UIList.push_back(new CMenuButton(b2Vec2(OCX * 0.5f, OCY * 0.5f + 40), b2Vec2(50, 20), L"Lab", true));
	m_UIList.push_back(new CMenuButton(b2Vec2(OCX * 0.5f, OCY * 0.5f + 80), b2Vec2(50, 20), L"Edit", true));
	m_UIList.push_back(new CMenuButton(b2Vec2(OCX * 0.5f, OCY * 0.5f + 120), b2Vec2(50, 20), L"Exit", true));
}

void CUIManager::LoadGameUI()
{
	m_UIList.push_back(new CInventoryPanel(b2Vec2_zero, b2Vec2(OCX, OCY), L"InventoryBackground", false));
	m_UIList.push_back(new CHotKeyPanel(b2Vec2(20, 20), b2Vec2_zero, L"HotKeyPanel", true));
	m_UIList.push_back(new CHUDPanel(b2Vec2(540, 20), b2Vec2_zero, L"HUD", true));
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
		LoadGameUI();
		break;
	case SCENEID::End:
		break;
	default:
		break;
	}
}

void CUIManager::MainMenu()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);
	for (auto& e : m_UIList)
	{
		if (e->m_tRect.Contains(Point(mouse.x, mouse.y)))
		{
			if (!e->m_bFocus)
			{
				e->m_bFocus = true;
				CAudioManager::GetInstance()->PlaySound(L"button_select.wav", CHANNELID::SOUND_EFFECT, 1.0f);
			}
			
			if (e->m_text == L"Start")
			{
				cout << "Mouse in StartButton\n";
				if (CKeyManager::GetInstance()->KeyDown(VK_LBUTTON))
				{
					GameStart();
					return;
				}
			}

			if (e->m_text == L"Lab")
			{
				cout << "Mouse in LabButton\n";
				if (CKeyManager::GetInstance()->KeyDown(VK_LBUTTON))
				{
					EnterTest();
					return;
				}
			}

			if (e->m_text == L"Edit")
			{
				cout << "Mouse in EditButton\n";
				if (CKeyManager::GetInstance()->KeyDown(VK_LBUTTON))
				{
					EnterEdit();
					return;
				}
			}

			if (e->m_text == L"Exit")
			{
				cout << "Mouse in ExitButton\n";
				if (CKeyManager::GetInstance()->KeyDown(VK_LBUTTON))
				{
					PostQuitMessage(0);
					return;
				}
			}
		}
		else
			e->m_bFocus = false;
	}
}

void CUIManager::InGame()
{
	if (CKeyManager::GetInstance()->KeyDown(VK_TAB))
	{
		for (auto& it : m_UIList)
		{
			if (it->m_text == L"InventoryBackground")
			{
				if (it->m_bShow)
				{
					CAudioManager::GetInstance()->PlaySound(L"inventory_close.wav", CHANNELID::SOUND_EFFECT, 0.8f);
				}
				else
				{
					CAudioManager::GetInstance()->PlaySound(L"inventory_open.wav", CHANNELID::SOUND_EFFECT, 0.8f);
				}
				it->m_bShow = !it->m_bShow;
				return;
			}
		}
		
	}
}

void CUIManager::Edit()
{

}

void CUIManager::PauseMenu()
{
	Clear();
}

void CUIManager::TestGame()
{
	if (CKeyManager::GetInstance()->KeyDown(VK_TAB))
	{
		for (auto& it : m_UIList)
		{
			if (it->m_text == L"InventoryBackground")
			{
				if (it->m_bShow)
				{
					CAudioManager::GetInstance()->PlaySound(L"inventory_close.wav", CHANNELID::SOUND_EFFECT, 0.8f);
				}
				else
				{
					CAudioManager::GetInstance()->PlaySound(L"inventory_open.wav", CHANNELID::SOUND_EFFECT, 0.8f);
				}
				it->m_bShow = !it->m_bShow;
			}
		}
	}
}

void CUIManager::OpenInventory()
{

}

void CUIManager::CloseInventory()
{

}
