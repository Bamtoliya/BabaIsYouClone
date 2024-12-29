#include "pch.h"
#include "Designs.h"
#include "CButton.h"


CButton::CButton(float fX, float fY, float w, float h, const TCHAR* sz, CUIElement* parent, bool show)
{
	m_parent = parent;
	if (m_parent)
	{
		m_tInfo = { m_parent->GetInfo().fX + fX, m_parent->GetInfo().fY + fY, w, h };
		m_parent->AddChild(this);
	}
	else m_tInfo = { fX, fY, w, h };
	m_text = sz;
	m_bShow = show;
}

void CButton::Update()
{
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(g_hWnd, &cursor);
	if (m_tRect.Contains(Point(cursor.x, cursor.y)))
	{
		m_bFocus = true;
		KeyInput();
	}
	else
	{
		m_bFocus = false;
	}
	__super::UpdateRect();
	__super::UpdateChild();
}

void CButton::Render(Graphics* graphic)
{
	if (m_bShow)
	{
		if (m_pImage)
		{

		}
		else
		{
			if (m_bFocus)
			{
				FillRoundedRect(graphic, m_tRect, 3, BORDERCOLOR, BORDERCOLOR);
			}
			else
			{
				FillRoundedRect(graphic, m_tRect, 3, BORDERCOLOR, FILLCOLOR);
			}

		}
	}
	if (g_bDevmode)
	{
		Pen pen(Color::Green);
		graphic->DrawRectangle(&pen, m_tRect);
	}
	__super::RenderChild(graphic);
}

void CButton::Render(HDC hDC)
{
	if (g_bDevmode)
	{
		HitBox(hDC, m_tRect);
	}
	__super::RenderChild(hDC);
}

void CButton::KeyInput()
{
	if (CKeyManager::GetInstance()->KeyDown(VK_LBUTTON))
	{
		OnClick();
	}
}

void CButton::OnClick()
{
	if (m_text == L"StartGame")
	{

	}
	if (m_text == L"Exit")
	{

	}
	if (m_text == L"")
	{

	}
	if (m_text == L"")
	{

	}
	if (m_text == L"")
	{

	}
	if (m_text == L"")
	{

	}
	if (m_text == L"")
	{

	}
}
