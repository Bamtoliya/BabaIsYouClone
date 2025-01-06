#include "pch.h"
#include "Designs.h"
#include "CWorldMap.h"
#include "CCursor.h"
#include "CLevelBlock.h"

void CWorldMap::Initialize()
{
	m_vCursor = {11, 15};
	m_tFrame = { 0, 0, 2, 0, 200, GetTickCount64() };
	m_grid.SetWidth(33);
	m_grid.SetHeight(18);
	m_grid.SetCenter(Vector2(OCX / 2, OCY / 2));
	m_grid.AddBlock(new CLevelBlock(), 9, 14);
	m_grid.AddBlock(new CLevelBlock(), 10, 13);
	m_grid.AddBlock(new CLevelBlock(), 11, 13);
	m_grid.AddBlock(new CLevelBlock(), 10, 12);
	m_grid.AddBlock(new CLevelBlock(), 11, 12);
	m_grid.AddBlock(new CLevelBlock(), 12, 12);
	m_grid.AddBlock(new CLevelBlock(), 10, 11);
	m_grid.AddBlock(new CLevelBlock(), 11, 11);
	m_Cursor = new CCursor();
	m_color = Color(255, 21, 24, 31);
	m_grid.AddBlock(m_Cursor, 9, 14);
	m_ullDelay = 100;
	m_ullLastInput = GetTickCount64();
	m_fTTime = 0.f;
	CSoundManager::GetInstance()->PlayBGM(L"map.ogg", 0.8f);
}

void CWorldMap::Update()
{
	KeyInput();
	if (m_bTransition) m_fTTime += 1.f;
	
	if (m_bTransition && m_fTTime >= 225.f)
	{
		m_bTransition = false, m_fTTime = 0.f;
		m_grid.EnterLevel(m_Cursor);
	}
	m_grid.Update();
}

void CWorldMap::LateUpdate()
{
	m_grid.LateUpdate();
	MoveFrame();
}

void CWorldMap::Render(Graphics* g)
{
#pragma region 월드맵 그리기
	Image* image = CResourceManager::GetInstance()->FindImage(L"WORLDMAP1");
	g->DrawImage(image, Rect(0, 0, OCX, OCY), 0, m_tFrame.iFrameStart * OCY, OCX, OCY, UnitPixel);
	SolidBrush brush(m_color);
	g->FillRectangle(&brush, Rect(0, 0, 31, OCY));
	g->FillRectangle(&brush, Rect(OCX - 31, 0, 31, OCY));
	g->FillRectangle(&brush, Rect(0, 0, OCX, 24));
	g->FillRectangle(&brush, Rect(0, OCY - 24, OCX, 24));
#pragma endregion
	m_grid.Render(g);
	m_grid.PrintLevel(m_Cursor, g, 0, 0);
	if (m_bTransition)
	{
		Transition(g);
		if (m_fTTime > 135.f && m_fTTime < 225.f)
		{
			m_grid.PrintLevel(m_Cursor, g, OCX/2, OCY/2);
		}
	}
}

void CWorldMap::Render(HDC hDC)
{

}

void CWorldMap::Enter()
{

}

void CWorldMap::Exit()
{

}

void CWorldMap::Clear()
{

}

void CWorldMap::Transition(Graphics* g)
{
	TransitionCloud(g, cosf(DEGTORAD(m_fTTime)), m_color);
}

void CWorldMap::MoveCursor(int x, int y)
{
	m_grid.MoveBlock(m_Cursor, x, y);
}

void CWorldMap::EnterLevel()
{
	//Transition(g);
}

void CWorldMap::KeyInput()
{
	if (m_ullLastInput + m_ullDelay < GetTickCount64())
	{
		if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
		{
			MoveCursor(-1, 0);
		}
		if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
		{
			MoveCursor(1, 0);
		}
		if (CKeyManager::GetInstance()->KeyPressing(VK_UP))
		{
			MoveCursor(0, -1);
		}
		if (CKeyManager::GetInstance()->KeyPressing(VK_DOWN))
		{
			MoveCursor(0, 1);
		}
		if (CKeyManager::GetInstance()->KeyPressing(VK_RETURN))
		{
			if (m_bTransition)
			{
				m_grid.EnterLevel(m_Cursor);
			}
			else
			{
				CSoundManager::GetInstance()->PlaySound(L"TRANSITION_ENTER.ogg", CHANNELID::SOUND_EFFECT, 0.8f);
				m_bTransition = true;
			}
			
		}
		m_ullLastInput = GetTickCount64();
	}
}

void CWorldMap::MoveFrame()
{
	if (m_tFrame.ullTime + m_tFrame.ullSpeed < GetTickCount64())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
		m_tFrame.ullTime = GetTickCount64();
	}
}
