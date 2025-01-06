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
	wstring tmp = L"";
	switch (m_eType)
	{
	case BLOCKTYPE::NONE:
		tmp = L"NONE";
		break;
	case BLOCKTYPE::TEXT:
		tmp = L"TEXT";
		break;
	case BLOCKTYPE::NOUN:
		tmp = L"NOUN";
		break;
	case BLOCKTYPE::VERB:
		tmp = L"VERB";
		break;
	case BLOCKTYPE::PROPERTY:
		tmp = L"PROPERTY";
		break;
	case BLOCKTYPE::CHARACTER:
		tmp = L"CHRACTER";
		break;
	case BLOCKTYPE::OBJECT:
		tmp = L"OBJECT";
		break;
	case BLOCKTYPE::TILE:
		tmp = L"TILE";
		break;
	case BLOCKTYPE::LEVEL:
		tmp = L"LEVEL";
		break;
	case BLOCKTYPE::CURSOR:
		tmp = L"CURSOR";
		break;
	case BLOCKTYPE::END:
		tmp = L"END";
		break;
	default:
		break;
	}
	Image* textImage = CResourceManager::GetInstance()->FindImage(L"TEXT_ALPHABET");
	float startX = 200 + (m_tRect.Width - lstrlenW(tmp.c_str()) * 16) / 2;
	float startY = 100 + (m_tRect.Height - 24) / 2;
	for (int i = 0; tmp[i] != _T('\0'); ++i) {
		Vector2 pos = CResourceManager::GetInstance()->FindText(tmp[i]);
		graphic->DrawImage(textImage, Rect(startX + 16 * i, startY, 24, 24), pos.x, pos.y, 24, 24, UnitPixel);
	}
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
	if (static_cast<int>(b) > static_cast<int>(BLOCKTYPE::NONE) && static_cast<int>(b) < static_cast < int>(BLOCKTYPE::END))
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
			UpdateList(L"LEVEL");
			break;
		case BLOCKTYPE::NOUN:
			UpdateList(L"NOUN");
			break;
		case BLOCKTYPE::VERB:
			UpdateList(L"VERB");
			break;
		case BLOCKTYPE::PROPERTY:
			UpdateList(L"PROPERTY");
			break;
		case BLOCKTYPE::TILE:
			UpdateList(L"TILE");
			break;
		default:
			UpdateList(L"TEXT");
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