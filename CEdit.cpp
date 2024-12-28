#include "pch.h"
#include "CEdit.h"
#include "Designs.h"
#include "CPlayer.h"

void CEdit::Initialize()
{
	CGameObjectManager::GetInstance()->AddObject(OBJID::BLOCK, CAbstractFactory<CPlayer>().Create());
	CGameObjectManager::GetInstance()->AddObject(OBJID::BLOCK, CAbstractFactory<CBlock>().Create());
	CBlockManager::GetInstance()->Initialize();
}

void CEdit::Update()
{
	KeyInput();
	CBlockManager::GetInstance()->Update();
}

void CEdit::LateUpdate()
{
	CBlockManager::GetInstance()->LateUpdate();
}

void CEdit::Render(Graphics* g)
{
	CBlockManager::GetInstance()->Render(g);
	//Pen pen(Color::White);
	////g->DrawLine(&pen, Point(100, 100), Point(100, WINCY));
	//for (int i = 0; i < WINCY; i+=TILECY)
	//{
	//	for (int j = 0; j < WINCX; j+=TILECX)
	//	{
	//		g->DrawLine(&pen, Point(j, 0), Point(j, WINCY));
	//	}
	//	g->DrawLine(&pen, Point(0, i), Point(WINCX, i));
	//}
}

void CEdit::Release()
{
}

void CEdit::KeyInput()
{
	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
	{
		CScrollManager::GetInstance()->SetScrollX(5.f);
	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
	{
		CScrollManager::GetInstance()->SetScrollX(-5.f);
	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_UP))
	{
		CScrollManager::GetInstance()->SetScrollY(5.f);
	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_DOWN))
	{
		CScrollManager::GetInstance()->SetScrollY(-5.f);
	}
	if (CKeyManager::GetInstance()->KeyPressing(VK_LBUTTON))
	{
		POINT	ptMouse{};
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		ptMouse.x -= (int)CScrollManager::GetInstance()->GetScrollX();
		ptMouse.y -= (int)CScrollManager::GetInstance()->GetScrollY();

		//CBlockManager::GetInstance()->PickBlock(Point(ptMouse.x, ptMouse.y), 1, 1);
	}

	if (CKeyManager::GetInstance()->KeyDown('S'))
	{
		CBlockManager::GetInstance()->SaveBlock();
		return;
	}

	if (CKeyManager::GetInstance()->KeyDown('L'))
	{
		CBlockManager::GetInstance()->LoadBlock();
		return;
	}
}

void CEdit::Render(HDC hDC)
{
}
