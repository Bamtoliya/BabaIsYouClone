#include "pch.h"
#include "CUIElement.h"

void CUIElement::UpdateRect()
{
	m_tRect.X = INT(m_tInfo.fX);
	m_tRect.Y = INT(m_tInfo.fY);
	m_tRect.Width = INT(m_tInfo.fCX);
	m_tRect.Height = INT(m_tInfo.fCY);
}

void CUIElement::UpdateChild()
{
	if (!m_child.size() == 0)
	{
		for (auto& c : m_child)
		{
			if(c) c->Update();
		}
	}
}

void CUIElement::RenderChild(Graphics* graphic)
{
	if (!m_child.size() == 0)
	{
		for (auto& c : m_child)
		{
			if(c) c->Render(graphic);
		}
	}
}

void CUIElement::RenderChild(HDC hDC)
{
	if (!m_child.size() == 0)
	{
		for (auto& c : m_child)
		{
			if(c) c->Render(hDC);
		}
	}
}
