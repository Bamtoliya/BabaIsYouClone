#include "pch.h"
#include "UIElements.h"
#include "CMainMenuUI.h"
#include "Designs.h"
#include "CTitle.h"

CMainMenuUI::CMainMenuUI()
{
	m_curFocus = nullptr;
	m_bShow = true;
	m_iFocusIndex = 0;
	new CTitle(217, 100, 419, 147, L"Title", this, true);
	new CMenuButton(327, 300, 200, 40, L"START", this, true);
	new CMenuButton(327, 350, 200, 40, L"EDIT", this, true);
	new CMenuButton(327, 400, 200, 40, L"EXIT", this, true);
}

void CMainMenuUI::Update()
{

	KeyInput();
	m_curFocus = dynamic_cast<CMenuButton*>(m_child[m_iFocusIndex]);
	__super::UpdateRect();
	__super::UpdateChild();
}

void CMainMenuUI::Render(Graphics* graphic)
{
	Image* image = SPRITE->FindImage(L"TEXT_CHARACTER_BABA");
	if (m_curFocus && m_iFocusIndex != 0)
	{
		graphic->DrawImage(image, Rect(327 - 40, m_curFocus->GetInfo().fY + 8, 24, 24), 51, 1, 24, 24, UnitPixel);
	}
	__super::RenderChild(graphic);
}

void CMainMenuUI::Render(HDC hDC)
{
	__super::RenderChild(hDC);
}

void CMainMenuUI::KeyInput()
{
	if (KEYIN->KeyDown(VK_UP))
	{
		if (m_iFocusIndex > 1) m_iFocusIndex--;
		wstring t = L"BUTTON_" + to_wstring((rand() % 6 + 1)) + L".ogg";
		CSoundManager::GetInstance()->PlaySound(t.c_str(), CHANNELID::SOUND_EFFECT, 0.8f);
	}
	if(KEYIN->KeyDown(VK_DOWN))
	{ 
		if(m_iFocusIndex < 3) m_iFocusIndex++;
		wstring t = L"BUTTON_" + to_wstring((rand() % 6 + 1)) + L".ogg";
		CSoundManager::GetInstance()->PlaySound(t.c_str(), CHANNELID::SOUND_EFFECT, 0.8f);
	}
	if (KEYIN->KeyDown(VK_RETURN))
	{
		m_curFocus->OnClick();
	}
}
