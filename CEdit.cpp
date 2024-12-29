#include "pch.h"
#include "CEdit.h"
#include "Designs.h"
#include "CPlayer.h"

void CEdit::Initialize()
{
	CBlockManager::GetInstance()->Initialize();
	CUIManager::GetInstance()->SetSceneID(SCENEID::Edit);
	m_iWidth = 10;
	m_iHeight = 10;
}

void CEdit::Update()
{
	KeyInput();
	CBlockManager::GetInstance()->Update();
	CUIManager::GetInstance()->Update();
}

void CEdit::LateUpdate()
{
	CUIManager::GetInstance()->LateUpdate();
	CBlockManager::GetInstance()->LateUpdate();
}

void CEdit::Render(Graphics* g)
{
	Pen pen(Color::White);
	int hW = m_iWidth / 2;
	int hH = m_iHeight / 2;
	for (int j = -hH; j < hH; ++j)
	{
		g->DrawLine(&pen, Point(OCX / 2 - hW * TILECX, OCY / 2 - j * TILECY), Point(OCX / 2 + hW * TILECX, OCY / 2 - j * TILECY));
		g->DrawLine(&pen, Point(OCX / 2 - hW * TILECX, OCY / 2 + j * TILECY), Point(OCX / 2 + hW * TILECX, OCY / 2 + j * TILECY));
	}
	for (int i = -hW; i < hW; ++i)
	{
		g->DrawLine(&pen, Point(OCX / 2 - i * TILECX, OCY / 2 - hH * TILECY), Point(OCX / 2 - i * TILECX, OCY / 2 + hH * TILECY));
		g->DrawLine(&pen, Point(OCX / 2 + i * TILECX, OCY / 2 - hH * TILECY), Point(OCX / 2 + i * TILECX, OCY / 2 + hH * TILECY));
	}
	CBlockManager::GetInstance()->Render(g);
	CUIManager::GetInstance()->Render(g);
}

void CEdit::Release()
{
}

void CEdit::KeyInput()
{
	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
	{
		if(m_iWidth > 2) m_iWidth -= 2;
	}
	if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
	{
		if(m_iWidth < 30) m_iWidth += 2;
	}
	if (CKeyManager::GetInstance()->KeyPressing(VK_UP))
	{
		if(m_iHeight < 16) m_iHeight += 2;
	}
	if (CKeyManager::GetInstance()->KeyPressing(VK_DOWN))
	{
		if (m_iHeight > 2) m_iHeight -= 2;
		
	}
	//PageDown
	if (CKeyManager::GetInstance()->KeyPressing(VK_NEXT))
	{

	}
	//PageUP
	if (CKeyManager::GetInstance()->KeyPressing(VK_PRIOR))
	{

	}
	if (CKeyManager::GetInstance()->KeyPressing(VK_RETURN))
	{
		CBlockManager::GetInstance()->Release();
		CBlockManager::GetInstance()->SetWidth(m_iWidth);
		CBlockManager::GetInstance()->SetHeight(m_iHeight);
		CBlockManager::GetInstance()->Initialize();
	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_LBUTTON))
	{
		cout << "LeftButton in Edit Called\n";
		POINT	ptMouse{};
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		ptMouse.x -= (int)CScrollManager::GetInstance()->GetScrollX();
		ptMouse.y -= (int)CScrollManager::GetInstance()->GetScrollY();

		//만약 마우스버튼이 그리드 위치라면
		/*if ()
		{

		}*/

		//CBlockManager::GetInstance()->PickBlock(Point(ptMouse.x, ptMouse.y));
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
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	int hW = m_iWidth / 2;
	int hH = m_iHeight / 2;

	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);

	//Draw Grid
	for (int j = -hH; j < hH; ++j)
	{
		MoveToEx(hDC, OCX / 2 - hW * TILECX, OCY / 2 - j * TILECY, NULL);
		LineTo(hDC, OCX / 2 + hW * TILECX, OCY / 2 - j * TILECY);
		MoveToEx(hDC, OCX / 2 - hW * TILECX, OCY / 2 + j * TILECY, NULL);
		LineTo(hDC, OCX / 2 + hW * TILECX, OCY / 2 + j * TILECY);
	}
	for (int i = -hW; i < hW; ++i)
	{
		MoveToEx(hDC, OCX / 2 - i * TILECX, OCY / 2 - hH * TILECY, NULL);
		LineTo(hDC, OCX / 2 - i * TILECX, OCY / 2 + hH * TILECY);
		MoveToEx(hDC, OCX / 2 + i * TILECX, OCY / 2 - hH * TILECY, NULL);
		LineTo(hDC, OCX / 2 + i * TILECX, OCY / 2 + hH * TILECY);
	}
	SelectObject(hDC, hOldPen);
	DeleteObject(hNewPen);
	CUIManager::GetInstance()->Render(hDC);
	CBlockManager::GetInstance()->Render(hDC);
	CGameObjectManager::GetInstance()->Render(hDC);
}
