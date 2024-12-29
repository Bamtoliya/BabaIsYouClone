#include "pch.h"
#include "CPanel.h"

CPanel::CPanel(float fX, float fY, float w, float h, const TCHAR* sz, CUIElement* parent, bool show)
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

void CPanel::Update()
{
	
	__super::UpdateRect();
	__super::UpdateChild();
}

void CPanel::Render(Graphics* graphic)
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

void CPanel::Render(HDC hDC)
{
	if (g_bDevmode)
	{
		HitBox(hDC, m_tRect);
	}
	__super::RenderChild(hDC);
}
