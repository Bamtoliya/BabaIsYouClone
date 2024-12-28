#include "pch.h"
#include "CBlock.h"
#include "Designs.h"

void CBlock::Initialize()
{
	m_tInfo = { 240, 240, 24, 24 };
	m_eWord = GAMEWORD::NOUN;
	m_eNoun = NOUN::BABA;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 1;
	m_tFrame.ullSpeed = 200;
	m_tFrame.ullTime = GetTickCount64();
}

void CBlock::Update()
{
	__super::UpdateRect();
}

void CBlock::LateUpdate()
{
	ChangeState();
	__super::MoveFrame();
}

void CBlock::Render(Graphics* graphic)
{
	Image* image = CResourceManager::GetInstance()->FindImage(L"Text_You");
	int tmp = 226 + m_tFrame.iFrameStart * 25;
	graphic->DrawImage(image, m_tRect, 276, tmp, 24, 24, UnitPixel);
	if (g_bDevmode)
	{
		Pen pen(Color::Red);
		graphic->DrawRectangle(&pen, m_tRect);
	}
}

void CBlock::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Text_You");
	//BitBlt(hDC, m_tRect.X, m_tRect.Y, m_tRect.Width, m_tRect.Height, hMemDC, 0, 0, 24, 24);
	StretchBlt(hDC, m_tRect.X, m_tRect.Y, m_tRect.X + m_tRect.Width, m_tRect.Y + m_tRect.Height, hMemDC, 0, 0, 24, 24, SRCCOPY);
	//BitBlt(hDC, m_tRect.X, m_tRect.Y, m_tRect.Width, m_tRect.Height, hMemDC, 0, 0, SRCCOPY);
	//GdiTransparentBlt(hDC, m_tRect.X, m_tRect.Y, m_tRect.Width, m_tRect.Height, hMemDC , 0, 0, 24, 24, RGB(255, 255, 255));
	if (g_bDevmode)
	{
		//Rectangle(hDC, m_tRect.X, m_tRect.Y, m_tRect.X + m_tRect.Width, m_tRect.Y + m_tRect.Height);
	}
}

void CBlock::Release()
{
}

void CBlock::OnCollision(CGameObject* op)
{
	switch (op->GetDIRECTION())
	{
	case DIRECTION::LEFT:
		m_tInfo.fX = op->GetInfo().fX - 48;
		break;
	case DIRECTION::RIGHT:
		m_tInfo.fX = op->GetInfo().fX + 48;
		break;
	case DIRECTION::UP:
		m_tInfo.fY = op->GetInfo().fY - 48;
		break;
	case DIRECTION::DOWN:
		m_tInfo.fY = op->GetInfo().fY + 48;
		break;
	}	
}

void CBlock::ChangeState()
{
	if (m_bActive)
	{
		m_tFrame.iMotion = 0;
	}
	else
	{
		m_tFrame.iMotion = 1;
	}
}



