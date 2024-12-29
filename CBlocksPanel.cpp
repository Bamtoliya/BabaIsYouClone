#include "pch.h"
#include "CBlocksPanel.h"
#include "CBlockButton.h"
#include "Designs.h"

CBlocksPanel::CBlocksPanel(float fX, float fY, float w, float h, const TCHAR* sz, CUIElement* parent, bool show) : m_pPreFocus(nullptr), m_pCurFocus(nullptr)
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

	int i = 0;
	int j = 0;
	for (auto& t : CResourceManager::GetInstance()->GetMap())
	{
		if (i > 20)
		{
			i = 0;
			j++;
		}
		if (_tcsstr(t.first, L"TEXT") != NULL)
		{
			new CBlockButton(i * 24, j * 24, 24, 24, t.first, this, true);
			i++;
		}
	}
	

	/*for (int i = 0; i < 20; ++i)
	{

	}
	new CBlockButton(0, 0, 24, 24, L"TEXT_YOU", this, true);
	new CBlockButton(24, 0, 24, 24, L"BABA", this, true);
	new CBlockButton(48, 0, 24, 24, L"BOX", this, true);
	new CBlockButton(72, 0, 24, 24, L"STAR", this, true);
	new CBlockButton(96, 0, 24, 24, L"STAR2", this, true);
	new CBlockButton(120, 0, 24, 24, L"TEXT_IS", this, true);*/
}

void CBlocksPanel::Update()
{
	__super::UpdateRect();
	__super::UpdateChild();
}

void CBlocksPanel::Render(Graphics* graphic)
{
	Pen pen(Color::Red);
	graphic->DrawRectangle(&pen, m_tRect);
	__super::RenderChild(graphic);
}

void CBlocksPanel::Render(HDC hDC)
{
}

void CBlocksPanel::SetFocus(CUIElement* c)
{
	c->Dump();
	if (m_pPreFocus != c)
	{
		m_pCurFocus = c;
		for (auto& e : m_child)
		{
			e.second->SetFocus(false);
		}
		m_pCurFocus->SetFocus(true);
	}
	m_pPreFocus = c;
}
