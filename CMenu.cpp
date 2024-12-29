#include "pch.h"
#include "CMenu.h"
#include "Designs.h"
#include "CGameObject.h"

void CMenu::Initialize()
{

}

void CMenu::Update()
{

}

void CMenu::LateUpdate()
{

}

void CMenu::Render(Graphics* g)
{
	Image* image = CResourceManager::GetInstance()->FindImage(L"TEXT_ALPHABET");
	//image
}

void CMenu::Release()
{
}

void CMenu::Render(HDC hDC)
{
}
