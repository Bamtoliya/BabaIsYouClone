#include "pch.h"
#include "CEdit.h"
#include "Designs.h"
#include "UIElements.h"

void CEdit::Initialize()
{
	CUIManager::DestroyInstance();
	CBlockManager::GetInstance()->Initialize();
	CUIManager::GetInstance()->SetSceneID(SCENEID::Edit);
	m_iWidth = 10;
	m_iHeight = 10;
	int hW = m_iWidth / 2;
	int hH = m_iHeight / 2;
}

void CEdit::Update()
{
	KeyInput();
	UpdateGridRect();
	CUIManager::GetInstance()->Update();
	CBlockManager::GetInstance()->Update();
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
	POINT	ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	if (gridRect.Contains(Point(ptMouse.x, ptMouse.y)))
	{
		//printf("GridRect: X: %d Y: %d WIDTH: %d HEIGHT: %d\n", gridRect.X, gridRect.Y, gridRect.Width, gridRect.Height);
		if (CKeyManager::GetInstance()->KeyPressing(VK_LBUTTON))
		{
			cout << "LeftButton in Edit Called\n";
			list<CUIElement*> UIList = CUIManager::GetInstance()->GetList();

			const TCHAR* targetText = L"BlocksPanel";
			auto it = find_if(UIList.begin(), UIList.end(), [&targetText](CUIElement* e) { return e->GetText() == targetText; });
			if (it != UIList.end())
			{
				if (dynamic_cast<CBlocksPanel*>(*it)->GetCurBlock())
				{
					dynamic_cast<CBlocksPanel*>(*it)->GetCurBlock()->Dump();
					CBlock curBlock = dynamic_cast<CBlockButton*>(dynamic_cast<CBlocksPanel*>(*it)->GetCurBlock())->GetTarget();
					ptMouse.x -= (int)CScrollManager::GetInstance()->GetScrollX();
					ptMouse.y -= (int)CScrollManager::GetInstance()->GetScrollY();
					CBlockManager::GetInstance()->PickBlock(Point(ptMouse.x, ptMouse.y), curBlock);
				}
			}
			else
			{

			}
		}
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

void CEdit::UpdateGridRect()
{
	int hW = m_iWidth / 2;
	int hH = m_iHeight / 2;
	gridRect = {
		OCX / 2 - hW * TILECX,
		OCY / 2 - hH * TILECY,
		m_iWidth * TILECX,
		m_iHeight * TILECX,
	};
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
