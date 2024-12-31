#include "pch.h"
#include "CMenu.h"
#include "Designs.h"
#include "CGameObject.h"

void CMenu::Initialize()
{
	CUIManager::GetInstance()->DestroyInstance();
	CUIManager::GetInstance()->SetSceneID(SCENEID::Menu);
}

void CMenu::Update()
{
	CUIManager::GetInstance()->Update();
}

void CMenu::LateUpdate()
{
	CUIManager::GetInstance()->LateUpdate();
}

void CMenu::Render(Graphics* g)
{
	CUIManager::GetInstance()->Render(g);
}

void CMenu::Release()
{
	CUIManager::DestroyInstance();
}

void CMenu::Render(HDC hDC)
{
	CUIManager::GetInstance()->Render(hDC);
}
