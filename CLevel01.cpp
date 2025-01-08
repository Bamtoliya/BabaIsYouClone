#include "pch.h"
#include "Designs.h"
#include "CLevel01.h"

void CLevel01::Initialize()
{
	CBlockManager::GetInstance()->LoadBlock(m_grid, L"Data/Level_01.dat");
	CSoundManager::GetInstance()->PlayBGM(L"burn.ogg", 0.8f);
	m_color = Color(255, 21, 24, 31);
	m_fTime = 0;
	m_szTitle = L"LAVA IS DEFEAT";
	m_bTransition = true;
}

void CLevel01::Update()
{
	KeyInput();
	if (m_bTransition) m_fTime += 0.5f;
	if (m_fTime >= 135.f) m_bTransition = false, m_fTime = 135;
	m_grid.Update();
}

void CLevel01::LateUpdate()
{
	m_grid.LateUpdate();
}

void CLevel01::Render(Graphics* g)
{
	//Border
	SolidBrush brush(m_color);
	g->FillRectangle(&brush, Rect(0, 0, 31, OCY));
	g->FillRectangle(&brush, Rect(OCX - 31, 0, 31, OCY));
	g->FillRectangle(&brush, Rect(0, 0, OCX, 24));
	g->FillRectangle(&brush, Rect(0, OCY - 24, OCX, 24));
	m_grid.Render(g);
}

void CLevel01::Render(HDC hDC)
{
}

void CLevel01::Release()
{
}

void CLevel01::Restart()
{
	CBlockManager::GetInstance()->LoadBlock(m_grid, L"Data/Level_01.dat");
	CSoundManager::GetInstance()->PlayBGM(L"burn.ogg", 0.8f);
}

void CLevel01::KeyInput()
{
	if (KEYIN->KeyDown(VK_ESCAPE))
	{
		CSoundManager::GetInstance()->PlayBGM(L"map.ogg", 0.8f);
		CSceneManager::GetInstance()->SetStage(nullptr);
	}
}
