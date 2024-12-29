#include "pch.h"
#include "CBlock.h"
#include "Designs.h"

void CBlock::Initialize()
{
	m_tInfo = { 240, 240, 24, 24 };
	m_eBlock = BLOCKTYPE::TEXT;
	m_eWord = GAMEWORD::NOUN;
	m_eNoun = NOUN::BABA;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 1;
	m_tFrame.ullSpeed = 200;
	m_tFrame.ullTime = GetTickCount64();
	m_pImgKey = L"TEXT_YOU";
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
	Image* image = CResourceManager::GetInstance()->FindImage(m_pImgKey);
	int x;
	int y;
	switch (m_eBlock)
	{
	case BLOCKTYPE::TEXT:
		if (m_bActive) x = 26;
		else x = 1;
		y = 1 + m_tFrame.iFrameStart * 25;
		break;
	case BLOCKTYPE::CHARACTER:
		break;
	case BLOCKTYPE::OBJECT:
		break;
	default:
		break;
	}
	
	graphic->DrawImage(image, m_tRect, x, y, 24, 24, UnitPixel);
	if (g_bDevmode)
	{
		Pen pen(Color::Red);
		graphic->DrawRectangle(&pen, m_tRect);
	}
}

void CBlock::Render(HDC hDC)
{
	
	/*Bitmap* bitmap = new Bitmap(image);
	HBITMAP hBitmap;
	HBITMAP hOldmap;
	bitmap->GetHBITMAP(Color(0,0,0), &hBitmap);*/
	
	/*Gdiplus::Image* image = CResourceManager::GetInstance()->FindImage(m_pImgKey);
	Graphics graphic(hDC);
	SolidBrush brush(Color(104, 46, 76));
	graphic.FillRectangle(&brush, m_tRect);
	graphic.DrawImage(image, m_tRect, 1, 1, 24, 24, UnitPixel);*/
	
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);
	//hOldmap = (HBITMAP)SelectObject(hMemDC, &hBitmap);
	GdiTransparentBlt(hDC, m_tRect.X, m_tRect.Y, m_tRect.Width, m_tRect.Height, hMemDC, 26, 1, 24, 24, RGB(84, 165, 75));
	//GdiTransparentBlt(hDC, m_tRect.X, m_tRect.Y, m_tRect.Width, m_tRect.Height, hMemDC, 1, 1, 24, 24, RGB(84, 165, 75));
	//BitBlt(hDC, m_tRect.X, m_tRect.Y, m_tRect.Width, m_tRect.Height, hMemDC, 26, 1, SRCCOPY);

	//StretchBlt(hDC, m_tRect.X, m_tRect.Y, m_tRect.X + m_tRect.Width, m_tRect.Y + m_tRect.Height, hMemDC, 0, 0, 24, 24, SRCCOPY);
	//BitBlt(hDC, m_tRect.X, m_tRect.Y, m_tRect.Width, m_tRect.Height, hMemDC, 0, 0, SRCCOPY);
	//GdiTransparentBlt(hDC, m_tRect.X, m_tRect.Y, m_tRect.Width, m_tRect.Height, hMemDC , 0, 0, 24, 24, RGB(255, 255, 255));
	//DeleteDC(hMemDC);
	if (g_bDevmode)
	{
		HitBox(hDC, m_tRect);
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
		m_tInfo.fX = op->GetInfo().fX - TILECX;
		break;
	case DIRECTION::RIGHT:
		m_tInfo.fX = op->GetInfo().fX + TILECX;
		break;
	case DIRECTION::UP:
		m_tInfo.fY = op->GetInfo().fY - TILECY;
		break;
	case DIRECTION::DOWN:
		m_tInfo.fY = op->GetInfo().fY + TILECY;
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



