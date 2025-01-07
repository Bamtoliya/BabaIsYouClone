#include "pch.h"
#include "Designs.h"
#include "CLevel00.h"

void CLevel00::Initialize()
{
	CBlockManager::GetInstance()->LoadBlock(m_grid, L"Data/Level_Test.dat");
	CSoundManager::GetInstance()->PlayBGM(L"baba.ogg", 0.8f);
	m_color = Color(255, 21, 24, 31);
	m_fTime = 0;
	m_szTitle = L"BABA IS YOU";
	m_bTransition = true;
}

void CLevel00::Update()
{
	KeyInput();
	if(m_bTransition) m_fTime += 0.5f;
	if (m_fTime >= 135.f) m_bTransition = false, m_fTime = 135;
	m_grid.Update();
}

void CLevel00::LateUpdate()
{
	m_grid.LateUpdate();
}

void CLevel00::Render(Graphics* g)
{
	//Border
	SolidBrush brush(m_color);
	g->FillRectangle(&brush, Rect(0, 0, 31, OCY));
	g->FillRectangle(&brush, Rect(OCX - 31, 0, 31, OCY));
	g->FillRectangle(&brush, Rect(0, 0, OCX, 24));
	g->FillRectangle(&brush, Rect(0, OCY - 24, OCX, 24));
	m_grid.Render(g);
}

void CLevel00::Render(HDC hDC)
{
	m_grid.Render(hDC);
}

void CLevel00::Release()
{
}

void CLevel00::KeyInput()
{
	if (KEYIN->KeyDown(VK_ESCAPE))
	{
		CSceneManager::GetInstance()->SetStage(nullptr);
	}
}
