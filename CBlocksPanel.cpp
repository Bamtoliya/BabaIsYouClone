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
			new CBlockButton((float)i * 24, (float)j * 24, 24, 24, t.first, BLOCKTYPE::TEXT, this, true);
			i++;
		}
	}
	i = 0;
	j++;
	for (auto& t : CResourceManager::GetInstance()->GetMap())
	{
		if (i > 20)
		{
			i = 0;
			j++;
		}
		if (_tcsstr(t.first, L"OBJECT") != NULL)
		{
			//_tc
			new CBlockButton((float)i * 24, (float)j * 24, 24, 24, t.first, BLOCKTYPE::OBJECT, this, true);
			i++;
		}
	}

	i = 0;
	j++;
	for (auto& t : CResourceManager::GetInstance()->GetMap())
	{
		if (i > 20)
		{
			i = 0;
			j++;
		}
		if (_tcsstr(t.first, L"CHARACTER") != NULL)
		{
			//_tc
			new CBlockButton((float)i * 24, (float)j * 24, 24, 24, t.first, BLOCKTYPE::CHARACTER, this, true);
			i++;
		}
	}
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
			//dynamic_cast<CBlockButton*>(e)->GetTarget().
			e->SetFocus(false);
		}
		m_pCurFocus->SetFocus(true);
	}
	m_pPreFocus = c;
}

void CBlocksPanel::UpdateList()
{
	//if(m_eType)
}
