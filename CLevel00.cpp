#include "pch.h"
#include "Designs.h"
#include "CLevel00.h"

void CLevel00::Initialize()
{
	CBlockManager::GetInstance()->LoadBlock(m_grid, L"Data/Level.dat");
	m_color = Color(255, 21, 24, 31);
	m_tRect1 = { -OCX / 2, -OCY /2, OCX, OCY};
	m_tRect2 = { OCX + OCX/2, -OCY/2, -OCX, OCY };
	m_tRect3 = { -OCX / 2, OCY + OCY / 2, OCX, -OCY };
	m_tRect4 = { OCX + OCX /2, OCY + OCY / 2, -OCX, -OCY};
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
	SolidBrush brush1(m_color);
	TransitionCloud(g, m_tRect1, cosf(DEGTORAD(m_fTime)), m_color);
	TransitionCloud(g, m_tRect2, cosf(DEGTORAD(m_fTime)), m_color);
	TransitionCloud(g, m_tRect3, cosf(DEGTORAD(m_fTime)), m_color);
	TransitionCloud(g, m_tRect4, cosf(DEGTORAD(m_fTime)), m_color);
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
