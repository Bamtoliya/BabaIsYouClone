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

	}
	
}

void CInGame::Render(Graphics* g)
{
	if (m_bWorld)
	{
		m_WorldMap->Render(g);
	}
	else if (m_bLevel)
	{
		//m_WorldMap->Render(g);
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
		//m_WorldMap->Render(g);
	}
}

void CInGame::Release()
{
	SafeDelete<CWorldMap*>(m_WorldMap);
	SafeDelete<CLevel*>(m_curLevel);
}
