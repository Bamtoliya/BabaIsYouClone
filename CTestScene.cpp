#include "pch.h"
#include "CTestScene.h"
#include "Designs.h"
#include "CPlayer.h"
#include "CBlock.h"


void CTestScene::Initialize()
{
	CBlockManager::GetInstance()->LoadBlock(m_grid, L"Data/Level.dat");
}

void CTestScene::Update()
{
	m_grid.Update();
}

void CTestScene::LateUpdate()
{
	m_grid.LateUpdate();
}

void CTestScene::Render(Graphics* g)
{
	m_grid.Render(g);
}

void CTestScene::Render(HDC hDC)
{
}

void CTestScene::Release()
{

}


