#include "pch.h"
#include "CUIElement.h"

void CUIElement::UpdateRect()
{
	m_tRect.X = INT(m_position.x);
	m_tRect.Y = INT(m_position.y);
	m_tRect.Width = INT(m_size.x);
	m_tRect.Height = INT(m_size.y);
}

void CUIElement::UpdateChild()
{
	if (!m_child.empty())
	{
		for (auto& c : m_child)
		{
			c.second->Update();
		}
	}
}

void CUIElement::RenderChild(Graphics* graphic)
{
	if (!m_child.empty())
	{
		for (auto& c : m_child)
		{
			c.second->Render(graphic);
		}
	}
}
