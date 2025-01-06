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

	//텍스트 출력
	SolidBrush brush(Color(255, 255, 255, 255));
	Image* textImage = CResourceManager::GetInstance()->FindImage(L"TEXT_ALPHABET");
	float startX = m_tRect.X + (m_tRect.Width - lstrlenW(m_text) * 16) / 2;
	float startY = m_tRect.Y + (m_tRect.Height - 24) / 2;
	for (int i = 0; m_text[i] != _T('\0'); ++i) {
		Vector2 pos = CResourceManager::GetInstance()->FindText(m_text[i]);
		graphic->DrawImage(textImage, Rect(startX+ 16 * i, startY, 24, 24), pos.x, pos.y, 24, 24, UnitPixel);
	}

	/*const WCHAR* tmp = m_text;
    graphic->DrawString(tmp, lstrlenW(tmp), &font, PointF(m_tRect.X + m_tRect.Width /2, m_tRect.Y + m_tRect.Height / 2), &format, &brush);*/
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
	if (m_text == L"START")
	{
		CSceneManager::GetInstance()->SetScene(SCENEID::Game);
		return;
	}
	if (m_text == L"EXIT")
	{
		PostQuitMessage(0);
		return;
	}
	if (m_text == L"EDIT")
	{
		CSceneManager::GetInstance()->SetScene(SCENEID::Edit);
		return;
	}
	if (m_text == L"SAVE")
	{

	}
	if (m_text == L"LOAD")
	{

	}
	if (m_text == L"RETURN")
	{
		CSceneManager::GetInstance()->SetScene(SCENEID::Menu);
		return;
	}
	if (m_text == L"")
	{

	}
}
