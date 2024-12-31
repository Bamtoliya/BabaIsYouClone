#include "pch.h"
#include "CInGame.h"
#include "Designs.h"

void CInGame::Initialize()
{
	//m_grid = new CGrid;
	m_tFrame = { 0, 0, 2, 0, 200, GetTickCount64() };
	m_grid.SetWidth(33);
	m_grid.SetHeight(18);
	m_grid.SetCenter(Vector2(OCX / 2, OCY / 2));
}

void CInGame::Update()
{
	
}

void CInGame::LateUpdate()
{
	MoveFrame();
}

void CInGame::Render(Graphics* g)
{
#pragma region 월드맵 그리기
	Image* image = CResourceManager::GetInstance()->FindImage(L"WORLDMAP1");
	g->DrawImage(image, Rect(0, 0, OCX, OCY), 0, m_tFrame.iFrameStart * OCY, OCX, OCY, UnitPixel);
	SolidBrush brush(Color(255, 21, 24, 31));
	g->FillRectangle(&brush, Rect(0, 0, 31, OCY));
	g->FillRectangle(&brush, Rect(OCX - 31, 0, 31, OCY));
	g->FillRectangle(&brush, Rect(0, 0, OCX, 24));
	g->FillRectangle(&brush, Rect(0, OCY - 24, OCX, 24));
#pragma endregion
	m_grid.Render(g);
}

void CInGame::Render(HDC hDC)
{
}

void CInGame::Release()
{
}

void CInGame::MoveFrame()
{
	if (m_tFrame.ullTime + m_tFrame.ullSpeed < GetTickCount64())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
		m_tFrame.ullTime = GetTickCount64();
	}
}
