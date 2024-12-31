#include "pch.h"
#include "CTitle.h"
#include "Designs.h"

CTitle::CTitle()
{
	m_bShow = true;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.ullSpeed = 200;
	m_tFrame.ullTime = GetTickCount64();
}

CTitle::CTitle(float fX, float fY, float w, float h, const TCHAR* sz, CUIElement* parent, bool show)
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
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.ullSpeed = 200;
	m_tFrame.ullTime = GetTickCount64();
}

void CTitle::Update()
{
	__super::UpdateRect();
	__super::UpdateChild();
	MoveFrame();
}

void CTitle::Render(Graphics* graphic)
{
	Image* image = CResourceManager::GetInstance()->FindImage(L"LOGO");
	graphic->DrawImage(image, m_tRect, 0, 0 + 147 * m_tFrame.iFrameStart, 419, 147, UnitPixel);
	if (g_bDevmode)
	{
		Pen pen(Color::Green);
		graphic->DrawRectangle(&pen, m_tRect);
	}
	__super::RenderChild(graphic);
}

void CTitle::Render(HDC hDC)
{

}

void CTitle::MoveFrame()
{
	if (m_tFrame.ullTime + m_tFrame.ullSpeed < GetTickCount64())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
		m_tFrame.ullTime = GetTickCount64();
	}
}
