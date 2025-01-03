#include "pch.h"
#include "Designs.h"
#include "CBlocksPanel.h"
#include "CBlockButton.h"


CBlockButton::CBlockButton()
{

}
CBlockButton::CBlockButton(float fX, float fY, float w, float h, const TCHAR* sz, CUIElement* parent, bool show)
{
	m_parent = parent;
	m_text = sz;
	if (m_parent)
	{
		m_tInfo = { m_parent->GetInfo().fX + fX, m_parent->GetInfo().fY + fY, w, h };
		m_parent->AddChild(this);
	}
	else m_tInfo = { fX, fY, w, h };

	m_bShow = show;
}
CBlockButton::CBlockButton(float fX, float fY, float w, float h, const TCHAR* sz, BLOCKTYPE type, CUIElement* parent, bool show)
{
	
	m_parent = parent;
	m_text = sz;
	if (m_parent)
	{
		m_tInfo = { m_parent->GetInfo().fX + fX, m_parent->GetInfo().fY + fY, w, h};
		m_parent->AddChild(this);
	}
	else m_tInfo = { fX, fY, w, h };
	m_bShow = show;
	m_target.SetPos(fX, fY);
	m_target.SetBlockType(type);
	m_target.SetImgKey(sz);
	if (_tcsstr(sz, L"TEXT") != NULL)
	{

	}
	m_target.UpdateRect();
}

void CBlockButton::Update()
{
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(g_hWnd, &cursor);
	if (m_tRect.Contains(Point(cursor.x, cursor.y)))
	{	
		KeyInput();
	}
	__super::UpdateRect();
	__super::UpdateChild();
}

void CBlockButton::Render(Graphics* graphic)
{
	//Background
	FillRoundedRect(graphic, m_tRect, 4, BORDERCOLOR, FILLCOLOR);
	//Load Image
	Image* image = CResourceManager::GetInstance()->FindImage(m_text);
	m_target.Render(graphic);
	
	if (m_bFocus)
	{
		Image* image = CResourceManager::GetInstance()->FindImage(L"FOCUS");
		graphic->DrawImage(image, m_tRect, 1, 1, 24, 24, UnitPixel);
	}
	if (g_bDevmode)
	{
		Pen pen(Color::Green);
		graphic->DrawRectangle(&pen, m_tRect);
	}
	//
	__super::RenderChild(graphic);
}

void CBlockButton::Render(HDC hDC)
{
	__super::RenderChild(hDC);
}

void CBlockButton::KeyInput()
{
	if (CKeyManager::GetInstance()->KeyDown(VK_LBUTTON))
	{
		dynamic_cast<CBlocksPanel*>(m_parent)->SetFocus(this);
	}
}

void CBlockButton::OnClick()
{
}
