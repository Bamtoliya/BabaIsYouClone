#include "pch.h"
#include "CInGame.h"

void CInGame::Initialize()
{
	m_WorldMap = new CWorldMap();
	m_WorldMap->Initialize();
}

void CInGame::Update()
{
	if (m_bWorld)
	{
		m_WorldMap->Update();
	}
	else
	{

	}
}

void CInGame::LateUpdate()
{
	m_WorldMap->LateUpdate();
}

void CInGame::Render(Graphics* g)
{
	m_WorldMap->Render(g);
}

void CInGame::Render(HDC hDC)
{
	m_WorldMap->Render(hDC);	
}

void CInGame::Release()
{
	SafeDelete<CWorldMap*>(m_WorldMap);
}
