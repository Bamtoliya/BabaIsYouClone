#include "pch.h"
#include "CCursor.h"
#include "Designs.h"

void CCursor::Initialize()
{

}

void CCursor::Update()
{
	__super::UpdateRect();
}

void CCursor::LateUpdate()
{
	__super::MoveFrame();
}

void CCursor::Render(Graphics* graphic)
{
	Image* image = CResourceManager::GetInstance()->FindImage(m_pImgKey);
	SolidBrush brush(Color::White);
	m_tRect = { m_tRect.X - 4, m_tRect.Y - 4, m_tRect.Width, m_tRect.Height };
	graphic->DrawImage(image, m_tRect, 1, 1 + m_tFrame.iFrameStart * 33, 32, 32, UnitPixel);
}

void CCursor::Render(HDC hDC)
{
}

void CCursor::Release()
{
}

void CCursor::OnCollision(CGameObject* op)
{
}
