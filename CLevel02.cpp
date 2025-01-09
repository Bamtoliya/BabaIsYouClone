#include "pch.h"
#include "Designs.h"
#include "CLevel02.h"

void CLevel02::Initialize()
{
	CBlockManager::GetInstance()->LoadBlock(m_grid, L"Data/Level_02.dat");
	CSoundManager::GetInstance()->PlayBGM(L"cave.ogg", 0.8f);
	m_color = Color(255, 21, 24, 31);
	m_fTime = 0;

	m_bTransition = false;
	m_bClear = false;
}

void CLevel02::Update()
{
	KeyInput();
	m_grid.Update();
	if (m_bClear && !m_bTransition)
	{
		CSoundManager::GetInstance()->PlaySound(L"TRANSITION_WIN.ogg", CHANNELID::SOUND_EFFECT, 0.8f);
		m_bTransition = true;
	}
	if (m_bTransition) m_fTime += 1.f;
	if (m_bTransition && m_fTime >= 225.f)
	{
		m_bTransition = false, m_fTime = 0.f;
		CSoundManager::GetInstance()->PlayBGM(L"map.ogg", 0.8f);
		CSceneManager::GetInstance()->SetStage(nullptr);
	}
}

void CLevel02::LateUpdate()
{
	m_grid.LateUpdate();
}

void CLevel02::Render(Graphics* g)
{
	//Border
	SolidBrush brush(m_color);
	g->FillRectangle(&brush, Rect(0, 0, 31, OCY));
	g->FillRectangle(&brush, Rect(OCX - 31, 0, 31, OCY));
	g->FillRectangle(&brush, Rect(0, 0, OCX, 24));
	g->FillRectangle(&brush, Rect(0, OCY - 24, OCX, 24));
	m_grid.Render(g);
	if (m_bTransition)
	{
		__super::WinTransition(g);
	}
}

void CLevel02::Render(HDC hDC)
{
}

void CLevel02::Release()
{
}

void CLevel02::Restart()
{
	CSoundManager::GetInstance()->PlaySound(L"TRANSITION_RESTART.ogg", CHANNELID::SOUND_EFFECT, 0.8f);
	CBlockManager::GetInstance()->LoadBlock(m_grid, L"Data/Level_02.dat");
	CSoundManager::GetInstance()->PlayBGM(L"cave.ogg", 0.8f);
	while (!m_undo.empty()) m_undo.pop();
}

void CLevel02::KeyInput()
{
	if (KEYIN->KeyDown(VK_ESCAPE))
	{
		CSoundManager::GetInstance()->PlayBGM(L"map.ogg", 0.8f);
		CSceneManager::GetInstance()->SetStage(nullptr);
	}
	if (KEYIN->KeyDown('R'))
	{
		Restart();
	}
	if (KEYIN->KeyDown('Z'))
	{
		Undo();
	}
}
