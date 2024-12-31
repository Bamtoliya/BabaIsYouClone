#include "pch.h"
#include "UIElements.h"
#include "CMainMenuUI.h"

CMainMenuUI::CMainMenuUI()
{
	m_bShow = true;
	new CTitle(217, 100, 419, 147, L"Title", this, true);
	new CButton(327, 300, 200, 40, L"START", this, true);
	new CButton(327, 350, 200, 40, L"EDIT", this, true);
	new CButton(327, 400, 200, 40, L"EXIT", this, true);
}

void CMainMenuUI::Update()
{
	__super::UpdateRect();
	__super::UpdateChild();
}

void CMainMenuUI::Render(Graphics* graphic)
{
	__super::RenderChild(graphic);
}

void CMainMenuUI::Render(HDC hDC)
{
	__super::RenderChild(hDC);
}
