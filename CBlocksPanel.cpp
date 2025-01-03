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
		if (i > 34)
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
	if(c) c->Dump();
	if (m_pPreFocus != c)
	{
		m_pCurFocus = c;
		for (auto& e : m_child)
		{
			e->SetFocus(false);
		}
		m_pCurFocus->SetFocus(true);
	}
	m_pPreFocus = c;
}


void CBlocksPanel::ChangeType(BLOCKTYPE b)
{
	if (static_cast<int>(b) > 0 && static_cast<int>(b) < 5)
	{
		m_eType = b;
		for_each(m_child.begin(), m_child.end(), SafeDelete<CUIElement*>);
		m_child.clear();

		switch (b)
		{
		case BLOCKTYPE::TEXT:
			UpdateList(L"TEXT");
			break;
		case BLOCKTYPE::CHARACTER:
			UpdateList(L"CHARACTER");
			break;
		case BLOCKTYPE::OBJECT:
			UpdateList(L"OBJECT");
			break;
		case BLOCKTYPE::LEVEL:
			//UpdateList(L"TEXT");
		case BLOCKTYPE::TILE:
			UpdateList(L"TILE");
			break;
		}
	}
}

void CBlocksPanel::UpdateList(const TCHAR* sz)
{
	int i = 0;
	int j = 0;
	for (auto& t : CResourceManager::GetInstance()->GetMap())
	{
		if (i > 34)
		{
			i = 0;
			j++;
		}
		if (_tcsstr(t.first, sz) != NULL)
		{
			//_tc
			new CBlockButton((float)i * 24, (float)j * 24, 24, 24, t.first, m_eType, this, true);
			i++;
		}
	}
}