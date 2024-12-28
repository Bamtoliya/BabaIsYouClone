#include "pch.h"
#include "CTestScene.h"
#include "Designs.h"

#include "CPlayer.h"
#include "CBlock.h"


void CTestScene::Initialize()
{
	CGameObjectManager::GetInstance()->AddObject(OBJID::BLOCK, CAbstractFactory<CPlayer>().Create());
	CGameObjectManager::GetInstance()->AddObject(OBJID::BLOCK, CAbstractFactory<CBlock>().Create());
}

void CTestScene::Update()
{
	CGameObjectManager::GetInstance()->Update();
}

void CTestScene::LateUpdate()
{
	CGameObjectManager::GetInstance()->LateUpdate();
}

void CTestScene::Render(Graphics* g)
{
	if (g_bDevmode)
	{
		Pen pen(Color::White);
		//DrawGrid
		for (int j = 1; j < TILEX - 1; ++j)
		{
			g->DrawLine(&pen, Point(j * TILECX, 0), Point(j * TILECX, WINCY));
		}
		for (int i = 1; i < TILEY-1; ++i)
		{	
			g->DrawLine(&pen, Point(0, i * TILECY), Point(WINCX, i * TILECY));
		}
	}
	CGameObjectManager::GetInstance()->Render(g);
}

void CTestScene::Release()
{

}

void CTestScene::Render(HDC hDC)
{
}
