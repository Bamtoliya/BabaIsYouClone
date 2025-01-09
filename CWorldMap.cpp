#include "pch.h"
#include "Designs.h"
#include "CWorldMap.h"
#include "CCursor.h"
#include "CLevelBlock.h"
#include "CLevel01.h"
#include "CLevel02.h"
#include "CLevel03.h"
#include "CLevel04.h"
#include "CLevel05.h"

void CWorldMap::Initialize()
{
	m_vCursor = {11, 15};
	m_tFrame = { 0, 0, 2, 0, 200, GetTickCount64() };
	m_grid.SetWidth(33);
	m_grid.SetHeight(18);
	m_grid.SetCenter(Vector2(OCX / 2, OCY / 2));
	m_grid.AddBlock(new CLevelBlock(new CLevel00, L"LEVEL_00"), 9, 14);
	m_grid.AddBlock(new CLevelBlock(new CLevel01, L"LEVEL_01"), 10, 13);
	m_grid.AddBlock(new CLevelBlock(new CLevel02, L"LEVEL_02"), 11, 13);
	m_grid.AddBlock(new CLevelBlock(new CLevel03, L"LEVEL_03"), 10, 12);
	m_grid.AddBlock(new CLevelBlock(new CLevel04, L"LEVEL_04"), 11, 12);
	m_grid.AddBlock(new CLevelBlock(new CLevel05, L"LEVEL_05"), 12, 12);
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
	m_grid.MoveCursor(m_Cursor, x, y);
}

void CWorldMap::EnterLevel()
{
	
}

void CWorldMap::KeyInput()
{
	if (m_ullLastInput + m_ullDelay < GetTickCount64())
	{
		wstring t = L"WALK_" + to_wstring((rand() % 5 + 1)) + L".ogg";
		if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
		{
			CSoundManager::GetInstance()->PlaySound(t.c_str(), CHANNELID::SOUND_EFFECT, 0.8f);
			MoveCursor(-1, 0);
			m_ullLastInput = GetTickCount64();
		}
		if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
		{
			CSoundManager::GetInstance()->PlaySound(t.c_str(), CHANNELID::SOUND_EFFECT, 0.8f);
			MoveCursor(1, 0);
			m_ullLastInput = GetTickCount64();
		}
		if (CKeyManager::GetInstance()->KeyPressing(VK_UP))
		{
			CSoundManager::GetInstance()->PlaySound(t.c_str(), CHANNELID::SOUND_EFFECT, 0.8f);
			MoveCursor(0, -1);
			m_ullLastInput = GetTickCount64();
		}
		if (CKeyManager::GetInstance()->KeyPressing(VK_DOWN))
		{
			CSoundManager::GetInstance()->PlaySound(t.c_str(), CHANNELID::SOUND_EFFECT, 0.8f);
			MoveCursor(0, 1);
			m_ullLastInput = GetTickCount64();
		}
		if (CKeyManager::GetInstance()->KeyDown(VK_RETURN))
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
			m_ullLastInput = GetTickCount64();
			
		}
		if (CKeyManager::GetInstance()->KeyDown(VK_ESCAPE))
		{
			CSceneManager::GetInstance()->SetScene(SCENEID::Menu);
			m_ullLastInput = GetTickCount64();
		}
		
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
