#include "pch.h"
#include "CInGame.h"

void CInGame::Initialize()
{
	m_bWorld = true;
	m_bLevel = false;
	m_WorldMap = new CWorldMap();
	m_WorldMap->Initialize();
}

void CInGame::Update()
{
	if (m_bWorld)
	{
		m_WorldMap->Update();
	}
	else if(m_bLevel)
	{
		//if(m_curLevel-)
		m_curLevel->Update();
	}
}

void CInGame::LateUpdate()
{
	if (m_bWorld)
	{
		m_WorldMap->LateUpdate();
	}
	else if (m_bLevel)
	{
		m_curLevel->LateUpdate();
	}
	
}

void CInGame::Render(Graphics* g)
{
	if (m_bWorld)
	{
		m_WorldMap->Render(g);
		//if(m_)
	}
	else if (m_bLevel)
	{
		m_curLevel->Render(g);
	}
	
}

void CInGame::Render(HDC hDC)
{
	if (m_bWorld)
	{
		m_WorldMap->Render(hDC);
	}
	else if (m_bLevel)
	{
		m_curLevel->Render(hDC);
	}
}

void CInGame::Release()
{
	SafeDelete<CWorldMap*>(m_WorldMap);
	SafeDelete<CLevel*>(m_curLevel);
}

void CInGame::SetLevel(CLevel* level)
{
	if (level)
	{
		m_curLevel = level;
		if(m_curLevel)
			m_curLevel->Initialize();
	}
	else
	{
		if (m_curLevel) m_curLevel = nullptr;
	}
}

void CInGame::EnterTransition(Graphics* g)
{

	/*TransitionCloud(g, m_tRect1, cosf(DEGTORAD(m_fTransitionTime)), m_color);
	TransitionCloud(g, m_tRect2, cosf(DEGTORAD(m_fTransitionTime)), m_color);
	TransitionCloud(g, m_tRect3, cosf(DEGTORAD(m_fTransitionTime)), m_color);
	TransitionCloud(g, m_tRect4, cosf(DEGTORAD(m_fTransitionTime)), m_color);*/
}

void CInGame::WinTransition(Graphics* g)
{

}

void CInGame::ReturnTransition(Graphics* g)
{

}
