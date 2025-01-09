#include "pch.h"
#include "CBlock.h"
#include "Designs.h"

CBlock::CBlock(float fX, float fY, const TCHAR* pImgKey, BLOCKTYPE b) :
	m_eBlock(b)
{
	m_tInfo = { fX, fY, 24, 24 };
	m_tRect = { (INT)fX, (INT)fY, 24, 24 };
	this->SetImgKey(pImgKey);

	m_tFrame.iFrameAnimation = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 1;
	m_tFrame.ullSpeed = 200;
	m_tFrame.ullTime = GetTickCount64();
}

void CBlock::Initialize()
{
	m_tInfo = { 240, 240, 24, 24 };
	m_eBlock = BLOCKTYPE::NONE;

	m_tFrame.iFrameAnimation = 0;
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
	Image* image = CResourceManager::GetInstance()->FindImage(m_pImgKey);
	if (image)
	{
		int x;
		int y;
		switch (m_eBlock)
		{
		case BLOCKTYPE::TEXT:
			if (m_bActive) x = 26;
			else x = 1;
			y = 1 + m_tFrame.iFrameStart * 25;
			break;
		case BLOCKTYPE::NOUN:
			if (m_bActive) x = 26;
			else x = 1;
			y = 1 + m_tFrame.iFrameStart * 25;
			break;
		case BLOCKTYPE::VERB:
			if (m_bActive) x = 26;
			else x = 1;
			y = 1 + m_tFrame.iFrameStart * 25;
			break;
		case BLOCKTYPE::PROPERTY:
			if (m_bActive) x = 26;
			else x = 1;
			y = 1 + m_tFrame.iFrameStart * 25;
			break;
		case BLOCKTYPE::CHARACTER:
			x = 51;
			y = 1 + m_tFrame.iFrameStart * 25;
			switch (m_eDir)
			{
			case DIRECTION::LEFT:
				x = 251;
				break;
			case DIRECTION::RIGHT:
				x = 51;
				break;
			case DIRECTION::UP:
				x = 151;
				break;
			case DIRECTION::DOWN:
				x = 351;
				break;
			}
			break;
		case BLOCKTYPE::OBJECT:
			x = 51;
			y = 1 + m_tFrame.iFrameStart * 25;
			break;
		case BLOCKTYPE::TILE:
			TileAssign(x);
			y = 1 + m_tFrame.iFrameStart * 25;
			break;
		default:
			x = 1;
			y = 1;
			break;
		}
		
		if (m_eBlock == BLOCKTYPE::CHARACTER)
		{
			graphic->DrawImage(image, m_tRect, x + m_tFrame.iFrameAnimation * 25, y, 23, 24, UnitPixel);
		}
		else if (m_pImgKey != L"TEXT_TILE_X")
		{
			graphic->DrawImage(image, m_tRect, x, y, 24, 24, UnitPixel);
		}
		else 
		{
			if (g_bDevmode || (CSceneManager::GetInstance()->GetCurrentScene() == SCENEID::Edit))
			{
				graphic->DrawImage(image, m_tRect, x, y, 24, 24, UnitPixel);
			}
		}
	}
	if (g_bDevmode)
	{
		Pen pen(Color::Red);
		graphic->DrawRectangle(&pen, m_tRect);
	}
}

void CBlock::Render(HDC hDC)
{
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
	switch (op->GetDirection())
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

void CBlock::Clone(CBlock& dst)
{
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

void CBlock::UpdateWord()
{
	if (_tcsstr(m_pImgKey, L"TEXT") != NULL)
	{
		m_eBlock = BLOCKTYPE::TEXT;
	}
	if (_tcsstr(m_pImgKey, L"TILE") != NULL)
	{
		m_eBlock = BLOCKTYPE::TILE;
	}
	if (_tcsstr(m_pImgKey, L"OBJECT") != NULL)
	{
		m_eBlock = BLOCKTYPE::OBJECT;
	}
	if (_tcsstr(m_pImgKey, L"CHARACTER") != NULL)
	{
		m_eBlock = BLOCKTYPE::CHARACTER;
	}
	if (_tcsstr(m_pImgKey, L"CURSOR") != NULL)
	{
		m_eBlock = BLOCKTYPE::CURSOR;
	}
}

void CBlock::Apply(CBlock* b)
{
	m_eBlock = b->m_eBlock;
	m_pImgKey = b->m_pImgKey;
}

void CBlock::TileAssign(int& x)
{
	bool l = m_bNeighbor[0];
	bool r = m_bNeighbor[1];
	bool u = m_bNeighbor[2];
	bool d = m_bNeighbor[3];
	if (!l && !r && !u && !d) x = 51;
	else if (!l && r && !u && !d) x = 76;
	else if (!l && !r && u && !d) x = 101;
	else if (!l && r && u && !d) x = 126;
	else if (l && !r && !u && !d) x = 151;
	else if (l && r && !u && !d) x = 176;
	else if (l && !r && u && !d) x = 201;
	else if (l && r && u && !d) x = 226;
	else if (!l && !r && !u && d) x = 251;
	else if (!l && r && !u && d) x = 276;
	else if (!l && !r && u && d) x = 301;
	else if (!l && r && u && d) x = 326;
	else if (l && !r && !u && d) x = 351;
	else if (l && r && !u && d) x = 376;
	else if (l && !r && u && d) x = 401;
	else if (l && r && u && d) x = 426;
}



